/*
 * constants.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */


#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <atomic>

#define BUFFER_LEN 128
#define NUM_CHANNELS 4
#define FREQ 44100
#define EPSILON 0.0000005
#define PI 3.14159265

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define PERIOD 50 //in nanoseconds

//define a global counter variable
//this will track "system ticks"
int COUNTS = 0;
//delta_t will track actual time delta in seconds
float DELTA_T = 1.0;
// N is the period of the sample signals (square, sine, etc)
std::atomic<int> N;
std::atomic<bool> buffer_filled;
//define a global clock for each thread
int CLOCK = 0;

#endif /* GLOBALS_H_ */
