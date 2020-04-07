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

	// TODO: make some sort of lock for data buffer in BH.
//	std::mutex data_buffer_mutex;
//	std::shared_ptr<std::mutex> DB_mutex_ptr = &data_buffer_mutex;

	//create classes to handle buffer filling and signal processing
	BufferHandler<double> BH;
	SignalProcessor<double> SP;
//	FilterHandler<double> FH;

	//TODO: create single thread that calls these two functions
//------------RUN PSEUDO CLOCK AND FILL BUFFER-----------//
	std::thread data_thread(&BufferHandler<double>::Run, &BH);
	data_thread.join();
//------------END RUN PSEUDO CLOCK AND FILL BUFFER-------//

//------------RUN SIGNAL PROCESSING ON EACH BUFFER-------//
	std::thread process_thread(&SignalProcessor<double>::FFT, &SP, BH.getBufferAddress());
	process_thread.join();
//------------END RUN SIGNAL PROCESSING ON EACH BUFFER---//

//------------RUN FILTER TO FILTER EACH DFT--------------//
//	std::thread filter();
//------------END RUN FILTER TO FILTER EACH DFT----------//

	//grab end time to determine total processing time
	t = clock() - t;
	std::cout << "Clicks: " << t << ", seconds: " << ((float)t/CLOCKS_PER_SEC) << std:: endl;

    return 0;
}
