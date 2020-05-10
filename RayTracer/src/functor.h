/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "rgb.h"

class functor {

	public:
		RGBTRIPLE operator()(int x, int y){
			//THIS IS THE BREAD AND BUTTER
			RGBTRIPLE rgb;
			uint8_t temp = (x + y) % 256;
			rgb.rgbtRed = temp;
			rgb.rgbtGreen = temp;
			rgb.rgbtBlue = temp;
			return rgb;
		}
};



#endif /* FUNCTOR_H_ */
