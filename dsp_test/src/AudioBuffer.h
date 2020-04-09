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
		bool buffer_filled;
		bool isCounterStarted;

	public:
		AudioBuffer(std::shared_ptr<std::mutex> mutex_ptr, T value) :
			BasicBuffer<T>(mutex_ptr, value){
			buffer_filled = false;
			isCounterStarted = false;
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
