/*
 * generators.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */
#include <time.h>
#include <math.h>
#include "constants.h"

void generateSquareWaveData(int ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = (((int)(i * DELTA_T) % N) < (N/2)) ? 1 : -1;
			}
		}
	}
}

void generateSineWaveData(int ** buffer, const int channel){
	for (int i = 0; i < BUFFER_LEN; i++){
		bool updated = false;
		while(CLOCK == 0){}
		while(CLOCK == 1){
			if (!updated){
				updated = true;
				buffer[channel][i] = sin(2 * PI * (float)FREQ * (float)(i * DELTA_T));
			}
		}
	}
}


