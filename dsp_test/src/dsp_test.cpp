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
#include <cmath>
#include <thread>
#include "functions.h"

#define BUFFER_LEN 32
#define NUM_CHANNELS 4

using namespace std;

int main() {
	//random file manipulation stuff
    fileManipulate();

    // create new 2-D array
    int **buffer = new int*[NUM_CHANNELS]; // allocate an array of 4 int pointers
    for (int i = 0; i < NUM_CHANNELS; ++i)
        buffer[i] = new int[BUFFER_LEN]; // these are our columns
//	initializeDB(buffer);
//
//	printArray(**buffer);

//	delete buffer;
    return 0;
}
