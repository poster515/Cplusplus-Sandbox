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
#include "functions.h"
#include "constants.h"
#include "generators.h"


using namespace std;

int main() {
//	//random file manipulation stuff, comment out for now
//    fileManipulate();

	// create thread that simply updates COUNTS, and detach
	clock_t t;
	auto f = [&t](){
		t = clock();
		COUNTS++;
		t = clock() - t;
		DELTA_T = ((float)t)/CLOCKS_PER_SEC;
		std::cout << "It took " << t << " clicks and "<< ((float)t)/CLOCKS_PER_SEC << " seconds.\n" << endl;
		N = (int) (1 / (FREQ * DELTA_T));
	};

	std::thread t1(f);
	t1.detach(); //don't need to sync with anything

    // create new 2-D array
    int **buffer = new int*[NUM_CHANNELS]; // allocate an array of 4 int pointers
    for (int i = 0; i < NUM_CHANNELS; ++i){
        buffer[i] = new int[BUFFER_LEN]; // these are our columns
    }
	initializeDB(buffer);
	printArray(buffer);

	//make four threads to update each buffer channel
	std::thread square_wave(generateSquareWaveData, buffer, CHANNEL_0);

	if (t1.joinable()) { t1.join(); }
	if (square_wave.joinable()) { square_wave.join(); }
	delete buffer;
    return 0;
}
