/*
 * SignalProcessor.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Jpost
 */

#ifndef SIGNALPROCESSOR_H_
#define SIGNALPROCESSOR_H_

template <typename T>
class SignalProcessor{
	private:
		T ** real_buffer; //NUM_CHANNELS deep with BUFFER_LEN data points
		T ** imag_buffer;

	public:
		SignalProcessor(){
			std::cout << "SP constructor called." << std::endl;
			this->real_buffer = initializeDB<T>(real_buffer);
			this->imag_buffer = initializeDB<T>(imag_buffer);
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
			std::cout << "In FFT function...just print." << std::endl;
			printArray<T>(data_buffer);


			for (int i = 0; i < BUFFER_LEN; ++i){
				for(int j = 0; j < BUFFER_LEN; ++j){

				}
			}
			// following code is from the internet...
			float pi2 = 2.0 * M_PI;
			float angleTerm,cosineA,sineA;
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
