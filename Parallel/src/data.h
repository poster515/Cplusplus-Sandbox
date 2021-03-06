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
		vector<T> data;

	public:
		Data(T init){
			data.push_back(init);
		}
		~Data(){
		}
		vector<T> * getDataAddress(){
			return &data;
		}
};

template <class T>
class Incrementer{
private:
		vector<T> * data;

	public:
		Incrementer(vector<T> * init){
			data = init;
		}
		~Incrementer(){

		}
		void IncrementData(int n){
			for (int i = 0; i < n; i++){
				(*data).back()++;
			}
		}
};
