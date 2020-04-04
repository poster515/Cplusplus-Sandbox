/*
 * buffer.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Jpost
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <thread>
#include <chrono>
#include <mutex>
#include "globals.h"
#include "functions.h"

using namespace std;
template <class T>
class BufferHandler {
	private:
		T ** buffer;

	public:
		BufferHandler(){
			std::cout << "BH constructor called." << std::endl;
			this->buffer = initializeDB<T>(buffer);
		}
		~BufferHandler(){
			std::cout << "BH destructor called." << std::endl;
			for (int i = 0; i < NUM_CHANNELS; ++i){
				delete[] buffer[i];
			}
			delete[] buffer;
		}

//		void Run(mutex &buffer_mutex){
		void Run(){

			//allow pseudo clock to run, and then run it
			buffer_filled = false;

			//run the counter until buffer is filled
			RunCounter();

			//lock buffer mutex while the buffer is filled
//			buffer_mutex.lock();
			BufferFill<T>(buffer);
//			buffer_mutex.unlock();

			//tell the pseudo clock it can stop counting
			buffer_filled = true;

			// just wait until t1 is safely destroyed
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));

			std::cout << "threads are joined" << std::endl;

			printArray<T>(buffer);

			//write all this data to a file, that a python notebook can read and plot
			writeToFile<T>(buffer);

		}
		T ** getBufferAddress(){
			return buffer;
		}

};

#endif /* BUFFER_HPP_ */
