/*
 * basicBuffer.h
 *
 *  Created on: Apr 8, 2020
 *      Author: Jpost
 */

#ifndef BASICBUFFER_H_
#define BASICBUFFER_H_

#include <memory>
#include <mutex>
#include <condition_variable>

#include "common_functions.h"

template <typename T>
class BasicBuffer{
    protected:
        T ** real_buffer;
        T ** imag_buffer;
        std::shared_ptr<std::mutex> real_mutex_ptr;
        std::condition_variable cv;

    public:
        BasicBuffer(std::shared_ptr<std::mutex> mutex_ptr, T value){
			//just using the "real_buffer" here
        	std::cout << "BB constructor called." << std::endl;
			this->real_buffer = initializeDB<T>(this->real_buffer, value);
			this->imag_buffer = initializeDB<T>(this->imag_buffer, value);
			this->real_mutex_ptr = mutex_ptr;
//			printArray<T>(real_buffer);
		}
        ~BasicBuffer(){
        	std::cout << "BB destructor called." << std::endl;
			for (int i = 0; i < NUM_CHANNELS; ++i){
				delete[] this->real_buffer[i];
				delete[] this->imag_buffer[i];
			}
			delete[] this->real_buffer;
			delete[] this->imag_buffer;
        }
        T ** getRealBufferAddress(){
        	return real_buffer;
        }
        T ** getImagBufferAddress(){
			return imag_buffer;
		}
};



#endif /* BASICBUFFER_H_ */
