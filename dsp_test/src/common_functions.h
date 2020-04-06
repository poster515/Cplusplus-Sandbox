/*
 * common_functions.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Jpost
 */

#ifndef COMMON_FUNCTIONS_H_
#define COMMON_FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include "globals.h"

using namespace std;

template <typename T>
T ** initializeDB(T ** buffer, const T init){
	buffer = new T*[NUM_CHANNELS];
	for (int i = 0; i < NUM_CHANNELS; i++){
		*(buffer + i) = new T[BUFFER_LEN];
//		buffer[i] = new T[BUFFER_LEN];		//alternate representation
		for(int j = 0; j < BUFFER_LEN; j++){
//			buffer[i][j] = (i*BUFFER_LEN)+j; //alternate representation
			*(*(buffer + i) + j) = init;
		}
	}
	return buffer;
}

template <typename T>
void printArray(T ** buffer){
	for (int i = 0; i < NUM_CHANNELS; i++){
		for(int j = 0; j < BUFFER_LEN; j++){
			std::cout << "buffer[" << i << "][" << j << "] = " << *(*(buffer + i) + j) << endl;
		}
	}
}
template <typename T>
void writeToFile(T **buffer, string &filename){
	// PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
	ofstream new_file;
    new_file.open(filename, ios::binary);
    new_file << "Square Wave, Sine Wave, Triangle Wave, Sawtooth Wave\n";
    for(int i = 0; i < BUFFER_LEN; i++){
    	new_file << buffer[0][i] << ", " << buffer[1][i] << ", " << buffer[2][i] << ", " << buffer[3][i] << "\n";
    }
    new_file.close();
}



#endif /* COMMON_FUNCTIONS_H_ */
