/*
 * SP_functions.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Jpost
 */

#ifndef SP_FUNCTIONS_H_
#define SP_FUNCTIONS_H_

/*
 * functions.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Jpost
 */
#include <cmath>
#include <complex>
#include "globals.h"

using namespace std;

template <typename T>
std::complex<T> **  initializeSP(std::complex<T> ** buffer, const T init){
	buffer = new std::complex<T>*[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++){
		*(buffer + i) = new std::complex<T>[BUFFER_LEN];
		for(int j = 0; j < BUFFER_LEN; j++){
			*(*(buffer + i) + j) = (init, init);
		}
	}
	return buffer;
}

//TODO: optimize this algorithm
template <typename T>
void performFFT(T ** data_buffer, T ** real_buffer, T ** imag_buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; ++i){
		for(int j = 0; j < BUFFER_LEN; ++j){
			// i is for each f_i element
			// j is for going through each array element and weighting
			float trig_arg = (2.0 * PI * i * j)/BUFFER_LEN;
			float real_product = data_buffer[channel][j] * cos(trig_arg);
			float imag_product = data_buffer[channel][j] * sin(trig_arg);
			real_buffer[channel][i] += real_product;
			imag_buffer[channel][i] -= imag_product;
		}
	}
}

#endif /* SP_FUNCTIONS_H_ */
