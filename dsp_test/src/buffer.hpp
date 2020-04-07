/*
 * buffer.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: Jpost
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <mutex>

#include "BH_functions.h"
#include "common_functions.h"
#include "globals.h"

using namespace std;
template <class T>
class BufferHandler {
	private:
		T ** buffer;

	public:
		BufferHandler(){
			std::cout << "BH constructor called." << std::endl;
			this->buffer = initializeDB<T>(buffer, -1.0);
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

			// print some stuff
			std::cout << "threads are joined" << std::endl;
			printArray<T>(buffer);

			//write all this data to a file, that a python notebook can read and plot
			std::string filename = "audio_samples.txt";
			writeToFile<T>(buffer, filename);

		}
		T ** getBufferAddress(){
			return buffer;
		}

};

#endif /* BUFFER_HPP_ */
