/*
 * filters.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Jpost
 */

#ifndef FILTERHANDLER_H_
#define FILTERHANDLER_H_

#include "BasicBuffer.h"
#include <vector>
using namespace std;

template <class T>
class FilterHandler : public BasicBuffer<T> {
	protected:
		void lowPassFilter(T**, T**, const int);
		vector<T> LPF;

	public:
		FilterHandler(std::shared_ptr<std::mutex> mutex_ptr, T value) :
			BasicBuffer<T>(mutex_ptr, value){

			//now initialize low pass filter vector
			for (int i = 0; i < BUFFER_LEN; ++i){
				// preferentially weight the lowest quarter of frequencies
				this->LPF.insert(this->LPF.end(), (i < (BUFFER_LEN / 4)) ? 1 : 0.33);
			}
		}
		~FilterHandler(){
			std::cout << "FH destructor called." << std::endl;
		}
		void filterDFT(T ** real_buffer, T ** imag_buffer);

};

#endif /* FILTERHANDLER_H_ */
