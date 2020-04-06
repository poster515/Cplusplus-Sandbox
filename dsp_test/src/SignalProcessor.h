/*
 * SignalProcessor.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_H_
#define SIGNALPROCESSOR_H_

#include <cmath>
//#include <complex>
#include <mutex>
#include "SP_functions.h"	// performFFT
#include "common_functions.h"	// printArray, initializeDB

template <typename T>
class SignalProcessor{
	private:
		T ** real_buffer; //NUM_CHANNELS deep with BUFFER_LEN data points
		T ** imag_buffer;
//		std::complex<T> ** buffer;

	public:
		SignalProcessor(){
			std::cout << "SP constructor called." << std::endl;
			this->real_buffer = initializeDB<T>(real_buffer, 0);
			this->imag_buffer = initializeDB<T>(imag_buffer, 0);
//			this->buffer = initializeDB<T>(buffer, 0);
		}
		~SignalProcessor(){
			std::cout << "SP destructor called." << std::endl;
			for (int i = 0; i < NUM_CHANNELS; ++i){
				delete[] real_buffer[i];
				delete[] imag_buffer[i];
			}
			delete[] real_buffer;
			delete[] imag_buffer;
		}
		void FFT(T ** data_buffer){
			//perform FFT on every channel in buffer
//			std::cout << "In FFT function...just printing." << std::endl;
//			printArray<T>(data_buffer);
//			printArray<T>(real_buffer);
//			printArray<T>(imag_buffer);
			// TODO: refactor to use <complex> library to simplify this whole class
			mutex mu;
			mu.lock();
			std::thread t1 (performFFT<float>, data_buffer, real_buffer, imag_buffer, CHANNEL_0);
			std::thread t2 (performFFT<float>, data_buffer, real_buffer, imag_buffer, CHANNEL_1);
			std::thread t3 (performFFT<float>, data_buffer, real_buffer, imag_buffer, CHANNEL_2);
			std::thread t4 (performFFT<float>, data_buffer, real_buffer, imag_buffer, CHANNEL_3);

			t1.join();
			t2.join();
			t3.join();
			t4.join();
			mu.unlock();

//			performFFT<float>(data_buffer, real_buffer, imag_buffer, CHANNEL_0);
//			performFFT<float>(data_buffer, real_buffer, imag_buffer, CHANNEL_1);
//			performFFT<float>(data_buffer, real_buffer, imag_buffer, CHANNEL_2);
//			performFFT<float>(data_buffer, real_buffer, imag_buffer, CHANNEL_3);

			printArray<T>(real_buffer);
			printArray<T>(imag_buffer);

			//write all this data to a file, that a python notebook can read and plot
			std::string filename = "DFT_real.txt";
			writeToFile<T>(real_buffer, filename);

			//write all this data to a file, that a python notebook can read and plot
			filename = "DFT_imag.txt";
			writeToFile<T>(imag_buffer, filename);
		}
};



#endif /* SIGNALPROCESSOR_H_ */
