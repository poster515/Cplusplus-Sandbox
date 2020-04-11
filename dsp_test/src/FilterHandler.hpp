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

	(*this->my_cond_ptr) = false; //just in case

	//wait for SP to complete it's processing
	while(!(*this->my_mutex_ptr).try_lock()){}
	while(!(*this->their_cond_ptr)){}
	while(!(*this->their_mutex_ptr).try_lock()){}

	std::thread t1 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_0);
	std::thread t2 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_1);
	std::thread t3 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_2);
	std::thread t4 (FilterHandler<T>::lowPassFilter, this, real_buffer, imag_buffer, CHANNEL_3);
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
	std::cout << "Filter threads are joined. FH owns print_mutex." << std::endl;

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "DFT_real_filtered.txt";
	writeToFile<T>(this->real_buffer, filename);

	//write all this data to a file, that a python notebook can read and plot
	filename = "DFT_imag_filtered.txt";
	writeToFile<T>(this->imag_buffer, filename);
	(*this->print_mutex_ptr).unlock();
	std::cout << "FH released print_mutex" <<std::endl;
};


#endif /* FILTERHANDLER_HPP_ */
