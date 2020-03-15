//============================================================================
// Name        : templates.cpp
// Author      : Joe Post
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include "calculator.h"

using namespace std;

int main() {

	int a = 3;
	int b = 2;
	float c = 3.5;
	float d = 2.0;

	Calculator<int> calc_int;
	Calculator<float> calc_float;

	calc_int.add(a, b);
	calc_float.multiply(c, d, c);

	cout << "float multiply: " << calc_float.getState() << endl;
	cout << "int multiply: " << calc_int.getState() << endl;

	//create array of integers
	vector<int> array_int;
	//crate array of floats
	vector<float> array_flt;

	cout << "enter number of elements of array: ";
	int length = 0;
	cin >> length;

	for(int i = 0; i < length; i++){
		array_int.push_back((int)i);
		array_flt.push_back((float)i + 0.5);
	}

	//print int array
	addAndPrintElements(array_int, 1);

	//print float array
	addAndPrintElements(array_flt, 1);

	return 0;
}
