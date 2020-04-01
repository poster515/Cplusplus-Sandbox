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
#include <chrono>
#include "functions.h"
#include "constants.h"
#include "generators.h"


using namespace std;

int main() {
	// create thread that simply updates COUNTS, and detach
	clock_t t;
	std::atomic_bool buffer_filled;
	auto f = [&](){
		CLOCK = 0;
		while(!buffer_filled){
			t = clock();
			std::this_thread::sleep_for(std::chrono::nanoseconds(PERIOD));
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

	//allow pseudo clock to run, and then run it
	buffer_filled = false;
	std::thread t1(f);
	t1.detach(); //don't need to sync with anything, or use join()

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

	//tell the pseudo clock it can stop counting
	buffer_filled = true;

	// just wait until t1 is safely destroyed
	// TODO: determine worst case time for t1 to stop
	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	std::cout << "threads are joined" << endl;

	printArray(buffer);

	//write all this data to a file, that a python notebook can read and plot
	writeToFile(buffer);

	//delete all allocated memory
	for (int i = 0; i < NUM_CHANNELS; ++i){
	    delete[] buffer[i];
	}
	delete[] buffer;

    return 0;
}
