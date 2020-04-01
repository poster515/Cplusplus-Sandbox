/*
 * constants.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */
#include <atomic>

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define BUFFER_LEN 32
#define NUM_CHANNELS 4
#define FREQ 44100
#define EPSILON 0.0000025
#define PI 3.14159265

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define PERIOD 50 //in nanoseconds

//define a global counter variable
//this will track "system ticks"
static int COUNTS = 0;
//delta_t will track actual time delta in seconds
static float DELTA_T = 1.0;
// N is the period of the sample signals (square, sine, etc)
std::atomic<int> N(1);
//define a global clock for each thread
static int CLOCK = 0;

#endif /* CONSTANTS_H_ */
