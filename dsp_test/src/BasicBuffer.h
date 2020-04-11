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

        //variables to track previous block's member states
        std::shared_ptr<std::mutex> their_mutex_ptr;
        std::shared_ptr<std::atomic<bool>> their_cond_ptr;

        //objects that are shared with other blocks
        std::mutex my_mutex;
        std::shared_ptr<std::mutex> my_mutex_ptr;

        std::atomic<bool> my_wait_cond;
        std::shared_ptr<std::atomic<bool>> my_cond_ptr;

        std::shared_ptr<std::mutex> print_mutex_ptr;

        //local to object, not shared.
        std::condition_variable cv;


    public:
        BasicBuffer(std::shared_ptr<std::mutex> their_mutex_ptr, std::shared_ptr<std::atomic<bool>> their_cond_ptr,
        		std::shared_ptr<std::mutex> print_mutex_ptr, T value){

        	std::cout << "BB constructor called." << std::endl;

        	//intitialize from constructor inputs
        	this->real_buffer = initializeDB<T>(this->real_buffer, value);
        	this->imag_buffer = initializeDB<T>(this->imag_buffer, value);
			this->their_mutex_ptr = their_mutex_ptr;
			this->their_cond_ptr = their_cond_ptr;
			this->print_mutex_ptr = print_mutex_ptr;

			//initialize some own items
			my_wait_cond = false;
			this->my_cond_ptr = (std::shared_ptr<std::atomic<bool>>)&my_wait_cond;
			this->my_mutex_ptr = (std::shared_ptr<std::mutex>)&my_mutex;

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
        std::shared_ptr<std::atomic<bool>> getMyCondPtr(){
        	return my_cond_ptr;
        }
        std::shared_ptr<std::mutex> getMyMutexPtr(){
			return my_mutex_ptr;
		}
};



#endif /* BASICBUFFER_H_ */
