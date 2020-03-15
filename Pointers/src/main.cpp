//============================================================================
// Name        : HelloWorld.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "test_classes.h"
#include "incrementer.h"

using namespace std;

int main(void) {
	//initialize new test state
	int new_state = 2;

	//create pointer to State object, and construct using test state
	State *state = new State(new_state);

	// now fetch the state of the "state" object and print
	int get_state = state->getState();
	cout << "current state = " << get_state << endl;

	//create pointer to State object, and construct using test state
	BasicState *basicstate = new BasicState();
	int * basicStateCurrentStatePtr = basicstate->getAddressOfCurrentState();
	cout << "current state of basicState = " << *basicStateCurrentStatePtr << endl;

	//now increment current_state of "state" by instantiating new incrementer object
	Incrementer * incrementer = new Incrementer(state);

	int count = 0;
	cout << "Enter number of times to increment state:" << endl;
	cin >> count;

	//now increment current_state of object state
	incrementer->IncrementState(count);

	//print current_state of state to make sure it's now 54
	cout << "New state: " << state->getState() << endl;

	// delete to prevent any memory leakage
	delete state;
	delete incrementer;
	return EXIT_SUCCESS;
}
