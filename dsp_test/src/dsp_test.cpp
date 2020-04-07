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
#include <mutex>

#include "buffer.hpp"
#include "SignalProcessor.h"
#include "filters.h"

using namespace std;

int main() {
	// grab start time in ticks
	clock_t t = clock();

	//declare a single mutex shared between the handler classes
	std::mutex data_buffer_mutex;
	std::shared_ptr<std::mutex> DB_mutex_ptr(&data_buffer_mutex);

	//create classes to handle buffer filling and signal processing
	BufferHandler<double> BH(DB_mutex_ptr);
	SignalProcessor<double> SP(DB_mutex_ptr);
	FilterHandler<double> FH;
//	InverseHandler<double> IH(DB_mutex_ptr);

	//run simultaneous threads to fill data buffer and immediately process
	std::thread data_thread(&BufferHandler<double>::Run, &BH);
	std::thread process_thread(&SignalProcessor<double>::FFT, &SP, BH.getBufferAddress());
//	std::thread filter_thread();
	data_thread.join();
	process_thread.join();
//	filter_thread.join();


	//grab end time to determine total processing time
	t = clock() - t;
	std::cout << "Clicks: " << t << ", seconds: " << ((float)t/CLOCKS_PER_SEC) << std:: endl;

    return 0;
}
