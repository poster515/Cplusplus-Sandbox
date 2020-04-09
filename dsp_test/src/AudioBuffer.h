/*
 * buffer.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Jpost
 */

#ifndef AUDIOBUFFER_H_
#define AUDIOBUFFER_H_

#include <mutex>
#include "common_functions.h"
#include "BasicBuffer.h"

using namespace std;

template <typename T>
class AudioBuffer : public BasicBuffer<T> {

	public:
		AudioBuffer(std::shared_ptr<std::mutex> mutex_ptr, T value) :
			BasicBuffer<T>(mutex_ptr, value){}

		~AudioBuffer(){
			std::cout << "AB destructor called." << std::endl;
		}

		//see AudioBuffer.hpp for declarations of the below functions
		void RunCounter();
		void BufferFill();
		void Run();
		T ** getBufferAddress(){
			return this->real_buffer;
		}
};

#endif /* AUDIOBUFFER_H_ */
