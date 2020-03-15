//============================================================================
// Name        : dsp_test.cpp
// Author      : Joe Post
// Version     :
// Copyright   : Your copyright notice
// Description : Saves raw MP3 data into vector object
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int sum = 0;
    // PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
    // first create file
    ofstream new_file;

    new_file.open("test.txt", ios::binary);
    new_file << "5\n";
    new_file.close();

    // now read that file
    ifstream inFile;

//	inFile.open("test.txt", ios::binary);
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
			sum += line.length();
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

    cout << "Sum = " << sum << endl;

    return 0;
}
