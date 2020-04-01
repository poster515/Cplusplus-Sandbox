/*
 * functions.h
 *
 *  Created on: Mar 30, 2020
 *      Author: Jpost
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <vector>
#include <cmath>
#include <thread>
#include "constants.h"

using namespace std;

void initializeDB(float ** buffer){

	for (int i = 0; i < NUM_CHANNELS; i++){
		for(int j = 0; j < BUFFER_LEN; j++){
//			buffer[i][j] = (i*BUFFER_LEN)+j; //alternate representation
			*(*(buffer + i) + j) = -1.0;
		}
	}
}

void printArray(float ** buffer){
	for (int i = 0; i < NUM_CHANNELS; i++){
		for(int j = 0; j < BUFFER_LEN; j++){
			cout << "buffer[" << i << "][" << j << "] = " << *(*(buffer + i) + j) << endl;
		}
	}
}

void writeToFile(float **buffer){
	// PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
	ofstream new_file;
    new_file.open("audio_samples.txt", ios::binary);
    new_file << "Square Wave, Sine Wave, Triangle Wave, Sawtooth Wave\n";
    for(int i = 0; i < BUFFER_LEN; i++){
    	new_file << buffer[0][i] << ", " << buffer[1][i] << ", " << buffer[2][i] << ", " << buffer[3][i] << "\n";
    }
    new_file.close();
}

