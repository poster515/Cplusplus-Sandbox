/*
 * generators.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */
#include <time.h>
#include <cmath>

#include "globals.h"

void generateSquareWaveData(float ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = ((i % N) < (N/2)) ? 1.0 : -1.0;
			}
		}
	}
}

void generateSineWaveData(float ** buffer, const int channel){

	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = sin((2 * PI * (i % N)) / N);
			}
		}
	}
}

void generateTriangleWaveData(float ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (i % N) < (N/2) ? (float)(i % N)/N : (1 - ((float)(i % N)/N));
			}
		}
	}
}

void generateSawtoothWaveData(float ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (float)(i % N) / N;
			}
		}
	}
}


