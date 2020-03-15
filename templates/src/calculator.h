/*
 * calculator.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Jpost
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include <memory>
#include <string>
#include <cstdlib>
#include <typeinfo>

using namespace std;

template <typename T>
void addAndPrintElements(vector<T> &in_a, int print){
	// gets pointer to array of type T
	// adds all elements and prints int times

	// initialize temp_sum with first element of a
	T temp_sum = (T)0;

	for (unsigned int i = 0; i < in_a.size(); i++){
		temp_sum = temp_sum + in_a.at(i);
		cout << "array element = " << in_a.at(i) << endl;
	}
	cout << "printing array" << endl;
	for (int i = 0; i < print; i++){
		cout << "Sum = " << temp_sum << endl;
	}

}

template <class T>
class Calculator{
	private:
		T internal_state;

	public:
		Calculator(){}
		~Calculator(){}

		void multiply(T in_a, T in_b){
			internal_state = in_a * in_b;
		}
		// declare additional multiply function that has a third argument
		void multiply(T in_a, T in_b, T temp = 2){
			internal_state = in_a * in_b * temp;
		}

		void add(T in_a, T in_b){
			internal_state = in_a + in_b;
		}

		T getState(){
			return internal_state;
		}
};




#endif /* CALCULATOR_H_ */
