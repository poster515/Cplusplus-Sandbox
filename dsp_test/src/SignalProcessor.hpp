/*
 * SIgnalProcessor.hpp
 *
 *  Created on: Apr 8, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_HPP_
#define SIGNALPROCESSOR_HPP_

#include <thread>
#include <complex>
#include "common_functions.h"
#include "globals.h"
#include "SignalProcessor.h"

using namespace std;

//TODO: optimize this algorithm
template <typename T>
void SignalProcessor<T>::performFFT(T ** data_buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; ++i){
		for(int j = 0; j < BUFFER_LEN; ++j){
			// i is for each f_i element
			// j is for going through each array element and weighting
			float trig_arg = (2.0 * PI * i * j)/BUFFER_LEN;
			float real_product = data_buffer[channel][j] * cos(trig_arg);
			float imag_product = data_buffer[channel][j] * sin(trig_arg);
			this->real_buffer[channel][i] += real_product;
			this->imag_buffer[channel][i] -= imag_product;
		}
	}
}

template <typename T>
void SignalProcessor<T>::FFT(T ** data_buffer){
	//perform FFT on every channel in buffer
	// TODO: refactor to use <complex> library to simplify this whole class

	std::lock_guard<std::mutex> lk(*this->real_mutex_ptr);
	//now we own the lock on this data
	std::thread t1 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_0);
	std::thread t2 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_1);
	std::thread t3 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_2);
	std::thread t4 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_3);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "DFT threads are joined. Printing arrays." << std::endl;
	printArray<T>(this->real_buffer);
	printArray<T>(this->imag_buffer);

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "DFT_real.txt";
	writeToFile<T>(this->real_buffer, filename);

	//write all this data to a file, that a python notebook can read and plot
	filename = "DFT_imag.txt";
	writeToFile<T>(this->imag_buffer, filename);
}

#endif /* SIGNALPROCESSOR_HPP_ */
