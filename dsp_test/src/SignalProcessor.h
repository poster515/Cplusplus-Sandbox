/*
 * SignalProcessor.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_H_
#define SIGNALPROCESSOR_H_

#include <iostream>
#include <cmath>
#include <mutex>
#include <vector>
#include "BasicBuffer.h"

using namespace std;

template <class T>
class SignalProcessor : public BasicBuffer<T> {
	public:
		SignalProcessor(std::shared_ptr<std::mutex> their_mutex_ptr, std::shared_ptr<std::atomic<bool>> their_cond_ptr,
				std::shared_ptr<std::mutex> print_mutex_ptr, T value) :
			BasicBuffer<T>(their_mutex_ptr, their_cond_ptr, print_mutex_ptr, value){}

		~SignalProcessor(){
			std::cout << "SP destructor called." << std::endl;
		}
		void FFT(T ** data_buffer);
		void performFFT(T ** data_buffer, const int channel);
};

#endif /* SIGNALPROCESSOR_H_ */
