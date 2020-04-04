/*
 * functions.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Jpost
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
#include "generators.h"
#include "globals.h"

using namespace std;

template <typename T>
T ** initializeDB(T ** buffer){
	buffer = new T*[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++){
		*(buffer + i) = new T[BUFFER_LEN];
//		buffer[i] = new T[BUFFER_LEN];		//alternate representation
		for(int j = 0; j < BUFFER_LEN; j++){
//			buffer[i][j] = (i*BUFFER_LEN)+j; //alternate representation
			*(*(buffer + i) + j) = -1.0;
		}
	}
	return buffer;
}

template <typename T>
void printArray(T ** buffer){
	for (int i = 0; i < NUM_CHANNELS; i++){
		for(int j = 0; j < BUFFER_LEN; j++){
			cout << "buffer[" << i << "][" << j << "] = " << *(*(buffer + i) + j) << endl;
		}
	}
}
template <typename T>
void writeToFile(T **buffer){
	// PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
	ofstream new_file;
    new_file.open("audio_samples.txt", ios::binary);
    new_file << "Square Wave, Sine Wave, Triangle Wave, Sawtooth Wave\n";
    for(int i = 0; i < BUFFER_LEN; i++){
    	new_file << buffer[0][i] << ", " << buffer[1][i] << ", " << buffer[2][i] << ", " << buffer[3][i] << "\n";
    }
    new_file.close();
}

template <typename T>
void BufferFill(T **buffer){
	//make four threads to update each buffer channel
	std::thread triangle_wave(generateTriangleWaveData, buffer, CHANNEL_2);
	std::thread square_wave(generateSquareWaveData, buffer, CHANNEL_0);
	std::thread sine_wave(generateSineWaveData, buffer, CHANNEL_1);
	std::thread sawtooth_wave(generateSawtoothWaveData, buffer, CHANNEL_3);

	//wait for each thread to complete
	square_wave.join();
	sine_wave.join();
	triangle_wave.join();
	sawtooth_wave.join();

//	generateSquareWaveData(buffer, CHANNEL_0);
//	generateSineWaveData(buffer, CHANNEL_1);
//	generateTriangleWaveData(buffer, CHANNEL_2);
//	generateSawtoothWaveData(buffer, CHANNEL_3);

}

void RunCounter(){
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

