/*
 * generators.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */
#include <time.h>
#include "constants.h"

void generateSquareWaveData(int ** buffer, const int channel){
	clock_t t = clock();

	for (int i = 0; i < BUFFER_LEN; i++){
		//calculate number of ticks elapsed ("actual time elapsed")
		t = clock();
		if (i == 0) {
			buffer[channel][i] = buffer[channel][BUFFER_LEN - 1];
		} else {
			t = clock() - t;
			DELTA_T = ((float)t)/CLOCKS_PER_SEC;
			N = (int) (1 / (FREQ * DELTA_T));
			buffer[channel][i] = ((i % N) < (N/2)) ? 1 : -1;
		}
	}
}


