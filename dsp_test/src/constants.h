/*
 * constants.h
 *
 *  Created on: Mar 31, 2020
 *      Author: Jpost
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define BUFFER_LEN 32
#define NUM_CHANNELS 4
#define FREQ 44100

#define CHANNEL_0 0
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3

//define a global counter variable
//this will track "system ticks"
static int COUNTS = 0;
//delta_t will track actual time delta in seconds
static float DELTA_T = 1.0;
//samples per second
static int N = 1;

#endif /* CONSTANTS_H_ */
