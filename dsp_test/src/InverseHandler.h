/*
 * InverseHandler.h
 *
 *  Created on: Apr 11, 2020
 *      Author: Jpost
 */

#ifndef INVERSEHANDLER_H_
#define INVERSEHANDLER_H_
#include <memory>
#include <mutex>
#include "BasicBuffer.h"

using namespace std;

template <class T>
class InverseHandler : public BasicBuffer<T> {
	public:
		InverseHandler(std::shared_ptr<std::mutex> their_mutex_ptr, std::shared_ptr<std::atomic<bool>> their_cond_ptr,
				std::shared_ptr<std::mutex> print_mutex_ptr, T value) :
			BasicBuffer<T>(their_mutex_ptr, their_cond_ptr, print_mutex_ptr, value){
		}

		~InverseHandler(){
			std::cout << "IH destructor called." << std::endl;
		}

		//see AudioBuffer.hpp for declarations of the below functions
		void performIFFT(T ** real_buffer, T ** imag_buffer, const int channel);
		void IFFT(T ** real_buffer, T ** imag_buffer);
};

#endif /* INVERSEHANDLER_H_ */
