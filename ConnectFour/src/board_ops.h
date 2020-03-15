/*
 * board_ops.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Jpost
 */

#ifndef BOARD_OPS_H_
#define BOARD_OPS_H_

#define NUM_ROWS 6
#define NUM_COLS 7

#include <vector>
#include <string>
#include "winning_patterns.h"
using namespace std;

vector<vector<string>> initialize_blank_board() {
	vector<vector<string>> temp_board;
	vector<string> temp_row;

	for(int i = 0; i < NUM_ROWS; i++){
		for(int j = 0; j < NUM_COLS; j++){
			temp_row.push_back("_");
		}
		temp_board.push_back(temp_row);
	}
	return temp_board;
}

bool check_ldiag(vector<vector<string>> &board){
	for(int i = 0; i < 3; i++){
		//first iterate over rows
		for(int j = 0; j < 4; j++){
			//then iterate over columns
			if	  (((board.at(i).at(j)     == board.at(i+1).at(j+1)) &&
					(board.at(i+1).at(j+1) == board.at(i+2).at(j+2)) &&
					(board.at(i+2).at(j+2) == board.at(i+3).at(j+3)) &&
					(board.at(i+3).at(j+3) == board.at(i).at(j)))    && board.at(i).at(j) != "_") {
				cout << "LEFT DIAG WINNER! " << board.at(i).at(j) << " WINS AT ROW " << i << " AND COLUMN " << j;
				return true;
			}
			if	  (((board.at(i).at(j+3)   == board.at(i+1).at(j+2)) &&
					(board.at(i+1).at(j+2) == board.at(i+2).at(j+1)) &&
					(board.at(i+2).at(j+1) == board.at(i+3).at(j))   &&
					(board.at(i+3).at(j)   == board.at(i).at(j+3)))  && board.at(i).at(j) != "_") {
				cout << "RIGHT DIAG WINNER! " << board.at(i).at(j) << " WINS AT ROW " << i+3 << " AND COLUMN " << j;
				return true;
			}
		}
	}
	return false;
}

bool check_horz(vector<vector<string>> &board){
	for(int i = 0; i < 6; i++){
		//first iterate over rows
		for(int j = 0; j < 4; j++){
			//then iterate over columns
			if	  (((board.at(i).at(j)   == board.at(i).at(j+1)) &&
					(board.at(i).at(j+1) == board.at(i).at(j+2)) &&
					(board.at(i).at(j+2) == board.at(i).at(j+3)) &&
					(board.at(i).at(j+3) == board.at(i).at(j)))  && board.at(i).at(j) != "_") {
				cout << "HORIZONTAL WINNER! " << board.at(i).at(j) << " WINS AT ROW " << i << " AND COLUMN " << j;
				return true;
			}
		}
	}
	return false;
}

bool check_vert(vector<vector<string>> &board){
	for(int i = 0; i < 3; i++){
		//first iterate over rows
		for(int j = 0; j < 7; j++){
			//then iterate over columns
			if	   (((board.at(i).at(j)   == board.at(i+1).at(j)) &&
					(board.at(i+1).at(j) == board.at(i+2).at(j))  &&
					(board.at(i+2).at(j) == board.at(i+3).at(j))  &&
					(board.at(i+3).at(j) == board.at(i).at(j)))   && board.at(i).at(j) != "_") {
				cout << "VERTICAL WINNER! " << board.at(i).at(j) << " WINS AT ROW " << i << " AND COLUMN " << j;
				return true;
			}
		}
	}
	return false;
}

bool no_winners(vector<vector<string>> &board){
	return !(check_ldiag(board) || check_horz(board) || check_vert(board));
}

void print_board(vector<vector <string>> &board){
	for(int i = 0; i < 6; i++){
		//first iterate over rows
		cout << "[ ";
		for(int j = 0; j < 7; j++){
			//then iterate over columns
			cout << board.at(i).at(j) << " ";
		}
		cout << "]" << endl;
	}
}

// detect if piece can be added piece to board and add it
bool run_gravity(vector<vector <string>> &board, int col, string piece){
	if ((6 < col) || (col < 0) || ((board.at(0).at(col)) != "_")){
		cout << "Invalid move, try again." << endl;
		return false;
	} else {
		for(int i = 0; i < 5; i++){
			if ((board.at(i).at(col) == "_") && (board.at(i+1).at(col) != "_")){
				board.at(i).at(col) = piece;
				break;
			} else if ((board.at(i+1).at(col) == "_") && ((i+1) == 5)){
				board.at(i+1).at(col) = piece;
				break;
			}
		}
	}
	return true;
}

#endif /* BOARD_OPS_H_ */
