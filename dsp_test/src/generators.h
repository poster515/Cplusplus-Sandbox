/*
 * generators.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */
#include <cmath>
#include "globals.h"

template <typename T>
void generateSquareWaveData(T ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (T)((i % N) < (N/2)) ? 1.0 : -1.0;
			}
		}
	}
}
template <typename T>
void generateSineWaveData(T ** buffer, const int channel){

	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (T)sin((2 * PI * (i % N)) / N);
			}
		}
	}
}
template <typename T>
void generateTriangleWaveData(T ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (i % N) < (N/2) ? (T)(4*(i % N))/N - 1 : 3 - (T)(4*(i % N))/N;
			}
		}
	}
}
template <typename T>
void generateSawtoothWaveData(T ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = ((T)(2 * (i % N)) / N) - 1;
			}
		}
	}
}


