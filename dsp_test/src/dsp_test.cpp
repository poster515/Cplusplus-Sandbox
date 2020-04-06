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

using namespace std;

int main() {
	// grab start time in ticks
	clock_t t = clock();

	//create classes to handle buffer filling and signal processing
	BufferHandler<float> BH;
	SignalProcessor<float> SP;

//------------RUN PSEUDO CLOCK AND FILL BUFFER-----------//
	std::thread data_thread(&BufferHandler<float>::Run, &BH);
//	data_thread.join();
//------------END RUN PSEUDO CLOCK AND FILL BUFFER-------//

//------------RUN SIGNAL PROCESSING ON EACH BUFFER-------//
	std::thread process_thread(&SignalProcessor<float>::FFT, &SP, BH.getBufferAddress());
	data_thread.join();
	process_thread.join();
//------------END RUN SIGNAL PROCESSING ON EACH BUFFER---//


	//grab end time to determine total processing time
	t = clock() - t;
	std::cout << "Clicks: " << t << ", seconds: " << ((float)t/CLOCKS_PER_SEC) << std:: endl;

    return 0;
}
