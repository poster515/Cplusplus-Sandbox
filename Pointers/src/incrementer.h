/*
 * incrementer.h
 *
 *  Created on: Mar 7, 2020
 *      Author: Jpost
 */

#ifndef INCREMENTER_H_
#define INCREMENTER_H_

#include "test_classes.h"

class Incrementer{

	private:
		State * state_ptr;
	public:
		Incrementer(State * ptr){
			state_ptr = ptr;
		};

		void IncrementState(int times = 100){
			for(int i = 0; i < times; i++){
				(*state_ptr->getStatePtr())++;
			}
		}
};

#endif /* INCREMENTER_H_ */
