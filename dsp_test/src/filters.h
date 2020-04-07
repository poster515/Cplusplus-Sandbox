/*
 * filters.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Jpost
 */

#ifndef FILTERS_H_
#define FILTERS_H_

template <class T>
class FilterHandler {
	private:
		std::shared_ptr<std::mutex> realDFT_mutex_ptr;
		std::shared_ptr<std::mutex> imagDFT_mutex_ptr;

	public:
		void filter(T ** real_buffer, T ** imag_buffer){

			T**(*filter_func)(T**);

			real_buffer = filter_func(real_buffer);
			imag_buffer = filter_func(imag_buffer);

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
