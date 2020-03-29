/*
 * main.cpp
 *
 *  Created on: Mar 16, 2020
 *      Author: Jpost
 */

#include <omp.h>
#include <vector>
#include <iostream>
#include <thread>
#include "data.h"
#include "functions.h"

using namespace std;

int main(void){
	//initialize some templated data class, each containing int vectors with a single value
	Data<int> d1(5);
	Data<int> d2(10);

	//now initialize some templated incrementer classes, each containing address of above vectors
	Incrementer<int> inc1(d1.getDataAddress());
	Incrementer<int> inc2(d2.getDataAddress());

	//next create some threads that add N elements to data
//	int num_times = 100;

	std::thread t1(inc1.addValueToLastElementNTimes(5, 10));

	t1.join();
	return 0;
}



