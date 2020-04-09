/*
 * FilterHandler.hpp
 *
 *  Created on: Apr 9, 2020
 *      Author: Jpost
 */

#ifndef FILTERHANDLER_HPP_
#define FILTERHANDLER_HPP_

#include <thread>
#include "common_functions.h"
#include "FilterHandler.h"

template <typename T>
void FilterHandler<T>::lowPassFilter(T ** real_buffer, T ** imag_buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; ++i){
		this->real_buffer[channel][i] = this->LPF.at(i) * real_buffer[channel][i];
		this->imag_buffer[channel][i] = this->LPF.at(i) * imag_buffer[channel][i];
	}
}

template <typename T>
void FilterHandler<T>::filterDFT(T ** real_buffer, T ** imag_buffer){
	std::lock_guard<std::mutex> lk(*this->real_mutex_ptr);
	std::thread t1 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_0);
	std::thread t2 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_1);
	std::thread t3 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_2);
	std::thread t4 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_3);
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "Filter threads are joined." << std::endl;

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "DFT_real_filtered.txt";
	writeToFile<T>(this->real_buffer, filename);

	//write all this data to a file, that a python notebook can read and plot
	filename = "DFT_imag_filtered.txt";
	writeToFile<T>(this->imag_buffer, filename);
};


#endif /* FILTERHANDLER_HPP_ */
