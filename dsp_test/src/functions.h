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
#define BUFFER_LEN 32
#define NUM_CHANNELS 4
using namespace std;

//void initializeDB(int *(*buffer)[NUM_CHANNELS][BUFFER_LEN]){
//
//	for (int i = 0; i < NUM_CHANNELS; i++){
//		for(int j = 0; j < BUFFER_LEN; j++){
//			(*(buffer + i) + j) = (i*NUM_CHANNELS)+j;
//		}
//	}
//}

void printArray(int *(*buffer)[NUM_CHANNELS][BUFFER_LEN]){
	for (int i = 0; i < NUM_CHANNELS; i++){
		for(int j = 0; j < BUFFER_LEN; j++){
			cout << *(*(buffer + i) + j) << endl;
		}
	}
}



void fileManipulate(){
    // PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
    // first create file
    ofstream new_file;

    new_file.open("test.txt", ios::binary);
    new_file << "5\n";
    new_file.close();


    ifstream inFile;

	inFile.open("2018-06-09_22_12_21_096_UTC.mp3", ios::binary);

	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	string line;
	vector<int> data;
	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			// store raw data into new vector
			cout << line.length() << endl;
			for(unsigned int i = 0; i < line.length(); i++){
				data.push_back(line.at(i));
			}
		}
	}
	// retrieve and print raw data
	inFile.close();
	for(unsigned int i = 0; i < data.size(); i++){
		cout << data.at(i) << endl;
		if (data.at(i) > 127 || data.at(i) < -128) {
			cout << "found weird data at byte: " << i << endl;
		}
	}
}

