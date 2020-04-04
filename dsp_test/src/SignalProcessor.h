/*
 * SignalProcessor.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_H_
#define SIGNALPROCESSOR_H_

#include <cmath>
#include <complex>

template <typename T>
class SignalProcessor{
	private:
		T ** real_buffer; //NUM_CHANNELS deep with BUFFER_LEN data points
		T ** imag_buffer;

	public:
		SignalProcessor(){
			std::cout << "SP constructor called." << std::endl;
			this->real_buffer = initializeDB<T>(real_buffer, 0);
			this->imag_buffer = initializeDB<T>(imag_buffer, 0);
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

			//declare some "re-usables"
			std::complex<T> complex_args(0.0, (2.0 * 3.14159)/BUFFER_LEN);
			std::complex<T> exponent = exp(complex_args);
			for (int k = 0; k < NUM_CHANNELS; ++k){
				for (int i = 0; i < BUFFER_LEN; ++i){
					for(int j = 0; j < BUFFER_LEN; ++j){
						// k is for going through each data channel
						// i is for each f_i element
						// j is for going through each array element and weighting
//						std::complex<T> product = (std::complex<float>(data_buffer[k][j],0.0) * pow(exponent, i*j));
//						real_buffer[k][i] += real(product);
//						imag_buffer[k][i] += imag(product);
						float trig_arg = (2.0 * PI * i * j)/BUFFER_LEN;
						float real_product = data_buffer[k][j] * cos(trig_arg);
						float imag_product = data_buffer[k][j] * sin(trig_arg);
						real_buffer[k][i] += real_product;
						imag_buffer[k][i] -= imag_product;
					}
				}
			}

			printArray<T>(real_buffer);
			printArray<T>(imag_buffer);

			//write all this data to a file, that a python notebook can read and plot
			std::string filename = "DFT_real.txt";
			writeToFile<T>(real_buffer, filename);

			//write all this data to a file, that a python notebook can read and plot
			filename = "DFT_imag.txt";
			writeToFile<T>(imag_buffer, filename);
			// following code is from the internet...

//			float pi2 = 2.0 * M_PI;
//			float angleTerm,cosineA,sineA;
//			float invs = 1.0 / 128;
//			for(unsigned int y = 0; y < 128; ++y) {
//				output_seq[y] = 0;
//				for(unsigned int x = 0; x < 128; ++x) {
//					angleTerm = pi2 * y * x * invs;
//					cosineA = cos(angleTerm);
//					sineA = sin(angleTerm);
//					output_seq[y].real += input_seq[x].real * cosineA - input_seq[x].imag * sineA;
//					output_seq[y].imag += input_seq[x].real * sineA + input_seq[x].imag * cosineA;
//				}
//				output_seq[y] *= invs;
//			}
		}

};



#endif /* SIGNALPROCESSOR_H_ */
