/*
 * winning_patterns.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Jpost
 */

#ifndef WINNING_PATTERNS_H_
#define WINNING_PATTERNS_H_

#include <vector>

using namespace std;

vector<vector<int>> LEFT_DIAG =    {{1, 0, 0, 0},
									{0, 1, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}};

vector<vector<int>> RIGHT_DIAG =   {{1, 0, 0, 0},
									{0, 1, 0, 0},
									{0, 0, 1, 0},
									{0, 0, 0, 1}};

vector<vector<int>> HORIZONTAL =   {{1, 1, 1, 1}};

vector<vector<int>> VERTICAL =     {{1},
									{1},
									{1},
									{1}};


#endif /* WINNING_PATTERNS_H_ */
