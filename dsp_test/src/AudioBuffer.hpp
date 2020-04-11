/*
 * buffer.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Jpost
 */

#ifndef AUDIOBUFFER_HPP_
#define AUDIOBUFFER_HPP_

#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>
#include "generators.h"
#include "AudioBuffer.h"
#include "globals.h"

using namespace std;

template <typename T>
void AudioBuffer<T>::RunCounter(){
	// create thread that simply updates COUNTS, and detach
	clock_t t;
	(*this->their_cond_ptr) = false;
	auto f = [&](){
			CLOCK = 0;
			while(!buffer_filled){
				t = clock();
				std::this_thread::sleep_for(std::chrono::nanoseconds(PERIOD));
				COUNTS = 0;
				CLOCK = 1 - CLOCK;
				t = clock() - t;
				DELTA_T = (((float)t)/CLOCKS_PER_SEC) + EPSILON;
				if ((int) (1 / (FREQ * DELTA_T)) > EPSILON){
					N = (int) (1 / (FREQ * DELTA_T));
				}
			}
		};
	std::thread t1(f);
	(*this->their_cond_ptr) = true; //let Run() know it can run
	t1.detach(); //don't need to sync with anything, or use join()
}


template <typename T>
void AudioBuffer<T>::BufferFill(){
	//we now own the lock.
	std::thread triangle_wave(generateTriangleWaveData<T>, this->real_buffer, CHANNEL_2);
	std::thread square_wave(generateSquareWaveData<T>, this->real_buffer, CHANNEL_0);
	std::thread sine_wave(generateSineWaveData<T>, this->real_buffer, CHANNEL_1);
	std::thread sawtooth_wave(generateSawtoothWaveData<T>, this->real_buffer, CHANNEL_3);

	//wait for each thread to complete
	square_wave.join();
	sine_wave.join();
	triangle_wave.join();
	sawtooth_wave.join();
}

template <typename T>
void AudioBuffer<T>::Run(){
	//allow pseudo clock to run, and then run it
	(this->my_wait_cond) = false; //just in case

	//wait for counter to start and lock my_mutex
	std::unique_lock<std::mutex> ulock(*this->my_mutex_ptr);
	this->cv.wait(ulock, [&]{ return (bool)(*this->their_cond_ptr); });
	std::cout << "AB now owns mutexes" <<std::endl;
	AudioBuffer<T>::BufferFill();
	ulock.unlock();

	//tell the pseudo clock it can stop counting
	(this->my_wait_cond) = true;

	// print some stuff
	while(!(*this->print_mutex_ptr).try_lock()){}
	std::cout << "threads are joined. AB own print_mutex." << std::endl;
	printArray<T>(this->real_buffer);

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "audio_samples.txt";
	writeToFile<T>(this->real_buffer, filename);
	(*this->print_mutex_ptr).unlock();
	std::cout << "AB released print_mutex" <<std::endl;

}

#endif /* AUDIOBUFFER_HPP_ */
