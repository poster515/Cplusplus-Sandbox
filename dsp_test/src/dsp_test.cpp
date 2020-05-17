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
#include "FilterHandler.hpp"
#include "InverseHandler.hpp"

using namespace std;

int main() {

	// grab start time in ticks
	clock_t t = clock();

	//declare some mutexes for each stage's resources
	std::mutex AB_mutex;
	std::shared_ptr<std::mutex> AB_mutex_ptr(&AB_mutex);
	std::atomic<bool> AB_wait_cond(false);
	std::shared_ptr<std::atomic<bool>> AB_cond_ptr(&AB_wait_cond);

	//mutex for accessing std::cout and file writing
	std::mutex print_mutex;
	std::shared_ptr<std::mutex> print_mutex_ptr(&print_mutex);

	//create classes to handle buffer filling and signal processing
	//want to initialize each block with dependent mutex and cond pointers
	AudioBuffer<double> AB(AB_mutex_ptr, AB_cond_ptr, print_mutex_ptr, -1.0);
	SignalProcessor<double> SP(AB.getMyMutexPtr(), AB.getMyCondPtr(), print_mutex_ptr, 0.0);
	FilterHandler<double> FH(SP.getMyMutexPtr(), SP.getMyCondPtr(), print_mutex_ptr, 0.0);
	InverseHandler<double> IH(FH.getMyMutexPtr(), FH.getMyCondPtr(), print_mutex_ptr, 0.0);

	//start counter for the AB thread
	AB.RunCounter();

//	AB.Run();
//	SP.FFT(AB.getRealBufferAddress());
//	FH.filterDFT(SP.getRealBufferAddress(), SP.getImagBufferAddress());
//	IH.IFFT(FH.getRealBufferAddress(), FH.getImagBufferAddress());

	//run threads to do everything
	std::thread data_thread(&AudioBuffer<double>::Run, &AB);
	std::thread DSP_thread(&SignalProcessor<double>::FFT, &SP, AB.getRealBufferAddress());
	std::thread filter_thread(&FilterHandler<double>::filterDFT, &FH, SP.getRealBufferAddress(), SP.getImagBufferAddress());
	std::thread inverse_thread(&InverseHandler<double>::IFFT, &IH, FH.getRealBufferAddress(), FH.getImagBufferAddress());

	data_thread.join();
	DSP_thread.join();
	filter_thread.join();
	inverse_thread.join();

	//grab end time to determine total processing time
	t = clock() - t;
	std::cout << "Clicks: " << t << ", seconds: " << ((float)t/CLOCKS_PER_SEC) << std:: endl;

    return 0;
}
