//============================================================================
// Name        : dsp_test.cpp
// Author      : Joe Post
// Version     :
// Copyright   : Your copyright notice
// Description : Saves raw MP3 data into vector object
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <vector>
#include <time.h>
#include <thread>
#include <mutex>
#include "functions.h"
#include "constants.h"
#include "generators.h"


using namespace std;

int main() {
//	//random file manipulation stuff, comment out for now
//    fileManipulate();

	// create thread that simply updates COUNTS, and detach
	clock_t t;
	static bool buffer_filled= false;
	auto f = [&](){
		CLOCK = 0;
		while(!buffer_filled){
			t = clock();
			while(COUNTS < 5000){ COUNTS++; }
			COUNTS = 0;
			CLOCK = 1 - CLOCK;
			t = clock() - t;
			DELTA_T = (((float)t)/CLOCKS_PER_SEC) + EPSILON;
			N = (int) (1 / (FREQ * DELTA_T));
			std::cout << "DELTA_T: " << DELTA_T << ", N: " << N << endl;
		}
	};

    // create new 2-D array
    float **buffer = new float*[NUM_CHANNELS]; // allocate an array of 4 int pointers
    for (int i = 0; i < NUM_CHANNELS; ++i){
        buffer[i] = new float[BUFFER_LEN]; // these are our columns
    }
	initializeDB(buffer);

	std::thread t1(f);
	t1.detach(); //don't need to sync with anything

	//make four threads to update each buffer channel
	std::thread square_wave(generateSquareWaveData, buffer, CHANNEL_0);
	std::thread sine_wave(generateSineWaveData, buffer, CHANNEL_1);
//	std::thread triangle_wave(generateTriangleWaveData, buffer, CHANNEL_2);
//	std::thread sawtooth_wave(generateSawtoothWaveData, buffer, CHANNEL_3);

	square_wave.join();
	sine_wave.join();
	buffer_filled = true; //tell the clock it can stop counting
	std::cout << "threads are joined" << endl;
	printArray(buffer);
	if (t1.joinable()) { t1.join(); }

	//delete all allocated memory
	for (int i = 0; i < NUM_CHANNELS; ++i){
	    delete[] buffer[i];
	}
	delete[] buffer;

    return 0;
}
