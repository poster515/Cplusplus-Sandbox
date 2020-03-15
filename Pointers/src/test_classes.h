/*
 * test_classes.h
 *
 *  Created on: Mar 7, 2020
 *      Author: Jpost
 */

#ifndef TEST_CLASSES_H_
#define TEST_CLASSES_H_

class BasicState {
	private:
		int currentState;

	public:
		// constructor i.e., setter
		BasicState(){
			currentState = 0;
		}

		// destructor
		virtual ~BasicState() {

		}

		int * getAddressOfCurrentState(){
			return &currentState;
		}

		int getState(){
			return currentState;
		}

};

// create new class that is inherits BasicState
class State : public BasicState {
	private:
		int currentState;

	public:
		// constructor
		State(int input_state) {
			currentState = input_state + 2;
		}

		int getState(){
			return currentState;
		}

		int * getStatePtr();
};

int* State::getStatePtr(void){
	return &currentState;
}

#endif /* TEST_CLASSES_H_ */
