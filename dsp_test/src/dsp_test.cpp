//============================================================================
// Name        : dsp_test.cpp
// Author      : Joe Post
// Version     :
// Copyright   : Your copyright notice
// Description : Saves raw MP3 data into vector object
//============================================================================

#include <iostream>
#include <time.h>
#include <mutex>
#include <thread>
#include "AudioBuffer.hpp"
#include "SignalProcessor.hpp"
#include "FilterHandler.h"

using namespace std;

int main() {

	// grab start time in ticks
	clock_t t = clock();

	//declare a single mutex shared between the handler classes
	std::mutex data_buffer_mutex;
	std::shared_ptr<std::mutex> DB_mutex_ptr(&data_buffer_mutex);

	//create classes to handle buffer filling and signal processing
	AudioBuffer<double> AB(DB_mutex_ptr, -1.0);
	SignalProcessor<double> SP(DB_mutex_ptr, 0.0);
//	FilterHandler<double> FH;
//	InverseHandler<double> IH(DB_mutex_ptr);

	//run simultaneous threads to fill data buffer and immediately process
	std::thread data_thread(&AudioBuffer<double>::Run, &AB);
	std::thread DSP_thread(&SignalProcessor<double>::FFT, &SP, AB.getBufferAddress());
//	std::thread filter_thread(&FilterHandler<double>::filterDFT, &FH, &SP);

	data_thread.join();
	DSP_thread.join();
//	filter_thread.join();

	//grab end time to determine total processing time
	t = clock() - t;
	std::cout << "Clicks: " << t << ", seconds: " << ((float)t/CLOCKS_PER_SEC) << std:: endl;

    return 0;
}
