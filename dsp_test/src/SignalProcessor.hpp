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
			T trig_arg = (2.0 * PI * i * j)/BUFFER_LEN;
			T real_product = data_buffer[channel][j] * cos(trig_arg);
			T imag_product = data_buffer[channel][j] * sin(trig_arg);
			this->real_buffer[channel][i] += real_product;
			this->imag_buffer[channel][i] -= imag_product;
		}
	}
}

template <typename T>
void SignalProcessor<T>::FFT(T ** data_buffer){

	(this->my_wait_cond) = false; //just in case
	while(!(*this->my_mutex_ptr).try_lock()){}
	while(!(*this->their_cond_ptr)){}
	while(!(*this->their_mutex_ptr).try_lock()){}

	//now SP owns locks on it's buffers and AB's buffers
	std::thread t1 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_0);
	std::thread t2 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_1);
	std::thread t3 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_2);
	std::thread t4 (&SignalProcessor<T>::performFFT, this, data_buffer, CHANNEL_3);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	//after threads are joined, release mutexes
	(*this->their_mutex_ptr).unlock();
	(*this->my_mutex_ptr).unlock();

	//let next stage know it can run
	(*this->my_cond_ptr) = true;

	//print some stuff
	while(!(*this->print_mutex_ptr).try_lock()){}
	std::cout << "DFT threads are joined. SP owns print_mutex." << std::endl;
	printArray<T>(this->real_buffer);
//	printArray<T>(this->imag_buffer);

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "DFT_real.txt";
	writeToFile<T>(this->real_buffer, filename);

	//write all this data to a file, that a python notebook can read and plot
	filename = "DFT_imag.txt";
	writeToFile<T>(this->imag_buffer, filename);
	(*this->print_mutex_ptr).unlock();
	std::cout << "SP released print_mutex" <<std::endl;
}

#endif /* SIGNALPROCESSOR_HPP_ */
