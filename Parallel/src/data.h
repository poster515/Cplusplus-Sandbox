/*
 * data.h
 *
 *  Created on: Mar 29, 2020
 *      Author: Jpost
 */

#include <omp.h>
#include <vector>
#include <thread>
using namespace std;


template <class T>
class Data{
	private:
		vector<T> * data;

	public:
		Data(T init){
			data->push_back(init);
		}
		~Data(){
			delete data;
		}
		vector<T> * getDataAddress(){
			return data;
		}
};


template <class T>
class Incrementer{
	private:
		vector<T> * data_ptr;

	public:
		Incrementer(vector<T> * init){
			data_ptr = init;
		}
		~Incrementer(){
			delete data_ptr;
		}

		void addElementToData(T value){
			data_ptr->push_back(value);
		}

		void addValueToLastElementNTimes(T value, int times){
			for (int i = 0; i < times; i++){
				data_ptr->back() =+ value;
			}
		}
};





