//============================================================================
// Name        : ConnectFour.cpp
// Author      : Joe Post
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include "board_ops.h"
using namespace std;

int main() {
	// function to select whether user inputs first move
//	string user_first;
	string user = "R";
	string comp = "B";

//	cout << "Would you like to start? (Y/n)" << endl;
//	cin >> user_first;

	int num_moves = 0; //keeps track of total number of moves and whose turn it is
	vector<vector<string>> board = initialize_blank_board();

	while(no_winners(board)) {
		// get user input or computer input
		if (num_moves % 2 == 0){
			// user plays
			cout << "Enter column number for piece [0 - 6]: ";
			int col; cin >> col;
			while(!run_gravity(board, col, user)){
				cin >> col;
			}
		} else {
			// computer plays
			cout << "Computer's turn..." << endl;
			// TODO: make better computer algorithm lol.
			run_gravity(board, rand() % 7, comp);
		}
		// print board
		print_board(board);
		num_moves++;
	}



	return 0;
}
