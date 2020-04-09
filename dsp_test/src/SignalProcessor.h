/*
 * SignalProcessor.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_H_
#define SIGNALPROCESSOR_H_

#include <cmath>
#include <mutex>
#include "BasicBuffer.h"

using namespace std;

template <class T>
class SignalProcessor : public BasicBuffer<T> {
	public:
		SignalProcessor(std::shared_ptr<std::mutex> mutex_ptr, T value) :
			BasicBuffer<T>(mutex_ptr, value){}

		~SignalProcessor(){
			std::cout << "SP destructor called." << std::endl;
		}
		void FFT(T ** data_buffer);
		void performFFT(T ** data_buffer, T ** real_buffer, T ** imag_buffer, const int channel);
};

#endif /* SIGNALPROCESSOR_H_ */
