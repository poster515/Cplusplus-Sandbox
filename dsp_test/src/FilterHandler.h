/*
 * filters.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Jpost
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "BasicBuffer.h"

template <class T>
class FilterHandler : BasicBuffer<T> {

	public:
		void filterDFT(SignalProcessor<double> &SP){

			T**(*filter_func)(T**);

			this->real_buffer = filter_func(this->real_buffer);
			this->imag_buffer = filter_func(this->imag_buffer);

//			std::thread t1 (performFFT<T>, data_buffer, real_buffer, imag_buffer, CHANNEL_0);
//			std::thread t2 (performFFT<T>, data_buffer, real_buffer, imag_buffer, CHANNEL_1);
//			std::thread t3 (performFFT<T>, data_buffer, real_buffer, imag_buffer, CHANNEL_2);
//			std::thread t4 (performFFT<T>, data_buffer, real_buffer, imag_buffer, CHANNEL_3);
//
//			t1.join();
//			t2.join();
//			t3.join();
//			t4.join();
		}
};



#endif /* FILTERS_H_ */
