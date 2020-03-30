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
	vector<int> data;
	data.push_back(10);

	//next create some threads that add N elements to data
	int num_times = 100;

	std::thread t1(addValueToLastElementNTimes, 5, &data, num_times*10);
	std::thread t2(addValueToLastElementNTimes, 7, &data, num_times*1000);
	std::thread t3(PrintLastElement, &data);

	if (t1.joinable()){
		cout << "t1 thread id: " << t1.get_id() << endl;
		t1.join();

	}
	if (t2.joinable()){
		cout << "t2 thread id: " << t2.get_id() << endl;
		cout << "t3 thread id: " << t3.get_id() << endl;
		t2.swap(t3);
		cout << "t2 new thread id: " << t2.get_id() << endl;
		cout << "t3 new thread id: " << t3.get_id() << endl;
		t2.join();
	}
	if (t3.joinable()){
		cout << "t3 thread id: " << t3.get_id() << endl;
		t3.join();
	}

	std::cout << "vector element = " << data.back() << std::endl;
	return 0;
}



