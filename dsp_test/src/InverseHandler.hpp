/*
 * InverseHandler.hpp
 *
 *  Created on: Apr 11, 2020
 *      Author: Jpost
 */

#ifndef INVERSEHANDLER_HPP_
#define INVERSEHANDLER_HPP_

#include <thread>
#include <cmath>
#include "InverseHandler.h"

template <typename T>
void InverseHandler<T>::performIFFT(T ** real_buffer, T ** imag_buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; ++i){
		for(int j = 0; j < BUFFER_LEN; ++j){
			// i is for each f_i element
			// j is for going through each array element and weighting
			T trig_arg = (2.0 * PI * i * j)/BUFFER_LEN;

			T real_product = (real_buffer[channel][j] * cos(trig_arg)) - (imag_buffer[channel][j] * sin(trig_arg));
			T imag_product = (imag_buffer[channel][j] * cos(trig_arg)) + (real_buffer[channel][j] * sin(trig_arg));

			this->real_buffer[channel][i] += real_product;
			this->imag_buffer[channel][i] += imag_product;
		}
		this->real_buffer[channel][i] /= BUFFER_LEN;
		this->imag_buffer[channel][i] /= BUFFER_LEN;
	}
}

template <typename T>
void InverseHandler<T>::IFFT(T ** real_buffer, T ** imag_buffer){

	(this->my_wait_cond) = false; //just in case
	while(!(*this->my_mutex_ptr).try_lock()){}
	while(!(*this->their_cond_ptr)){}
	while(!(*this->their_mutex_ptr).try_lock()){}

	//now IH owns locks on it's buffers and AB's buffers
	std::thread t1 (&InverseHandler<T>::performIFFT, this, real_buffer, imag_buffer, CHANNEL_0);
	std::thread t2 (&InverseHandler<T>::performIFFT, this, real_buffer, imag_buffer, CHANNEL_1);
	std::thread t3 (&InverseHandler<T>::performIFFT, this, real_buffer, imag_buffer, CHANNEL_2);
	std::thread t4 (&InverseHandler<T>::performIFFT, this, real_buffer, imag_buffer, CHANNEL_3);

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
	std::cout << "IDFT threads are joined. IH owns print_mutex." << std::endl;
	printArray<T>(this->real_buffer);
//	printArray<T>(this->imag_buffer);

	//write all this data to a file, that a python notebook can read and plot
	std::string filename = "IDFT_real.txt";
	writeToFile<T>(this->real_buffer, filename);

	//write all this data to a file, that a python notebook can read and plot
	filename = "IDFT_imag.txt";
	writeToFile<T>(this->imag_buffer, filename);
	(*this->print_mutex_ptr).unlock();
	std::cout << "IH released print_mutex" <<std::endl;
}



#endif /* INVERSEHANDLER_HPP_ */
