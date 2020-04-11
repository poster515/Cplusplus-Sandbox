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
	private:
		std::atomic<bool> isCounterStarted;

	public:
		AudioBuffer(std::shared_ptr<std::mutex> their_mutex_ptr, std::shared_ptr<std::atomic<bool>> their_cond_ptr,
				std::shared_ptr<std::mutex> print_mutex_ptr, T value) :
			BasicBuffer<T>(their_mutex_ptr, their_cond_ptr, print_mutex_ptr, value){
		}

		~AudioBuffer(){
			std::cout << "AB destructor called." << std::endl;
		}

		//see AudioBuffer.hpp for declarations of the below functions
		void RunCounter();
		void BufferFill();
		void Run();
		T ** getBufferAddress();
};

#endif /* AUDIOBUFFER_H_ */
