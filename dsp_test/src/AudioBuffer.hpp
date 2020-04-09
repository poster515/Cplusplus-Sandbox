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
				std::cout << "DELTA_T: " << DELTA_T << ", N: " << N << endl;
			}
		};

	std::thread t1(f);
	t1.detach(); //don't need to sync with anything, or use join()
}


template <typename T>
void AudioBuffer<T>::BufferFill(){
	//make four threads to update each buffer channel
//	mutex mu;
//	mu.lock();
	std::thread triangle_wave(generateTriangleWaveData<T>, this->real_buffer, CHANNEL_2);
	std::thread square_wave(generateSquareWaveData<T>, this->real_buffer, CHANNEL_0);
	std::thread sine_wave(generateSineWaveData<T>, this->real_buffer, CHANNEL_1);
	std::thread sawtooth_wave(generateSawtoothWaveData<T>, this->real_buffer, CHANNEL_3);

	//wait for each thread to complete
	square_wave.join();
	sine_wave.join();
	triangle_wave.join();
	sawtooth_wave.join();
//	mu.unlock();

//	generateSquareWaveData(buffer, CHANNEL_0);
//	generateSineWaveData(buffer, CHANNEL_1);
//	generateTriangleWaveData(buffer, CHANNEL_2);
//	generateSawtoothWaveData(buffer, CHANNEL_3);

}

template <typename T>
void AudioBuffer<T>::Run(){

	//allow pseudo clock to run, and then run it
	buffer_filled = false;

	//run the counter until buffer is filled
	AudioBuffer::RunCounter();

	//lock buffer mutex while the buffer is filled
	while(!(*this->real_mutex_ptr).try_lock()){}
	AudioBuffer<T>::BufferFill();
	(*this->real_mutex_ptr).unlock();

	//tell the pseudo clock it can stop counting
	buffer_filled = true;

	// print some stuff
	std::cout << "threads are joined" << std::endl;
	printArray<T>(this->real_buffer);

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "audio_samples.txt";
	writeToFile<T>(this->real_buffer, filename);

}


#endif /* AUDIOBUFFER_HPP_ */
