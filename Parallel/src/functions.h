/*
 * functions.h
 *
 *  Created on: Mar 29, 2020
 *      Author: Jpost
 */
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void PrintElements(const vector<T> * a){
	for (unsigned int i = 0; i < a->size(); i++){
		std::cout << "vector element = " << a->at(i) << std::endl;
	}
}

template<typename T>
void multiply(T in_a, T in_b){
	 in_a * in_b;
}

template<typename T>
void add(T in_a, T in_b){

}

void addValueToLastElementNTimes(int value, vector<int> * data_ptr, int times){
	for (int i = 0; i < times; i++){
		data_ptr->back() += value;
	}
}

void PrintLastElement(const vector<int> * a){
	std::cout << "vector element = " << a->back() << std::endl;
}
