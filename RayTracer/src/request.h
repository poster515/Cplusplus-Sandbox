/*
 * request.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <mutex>
#include <memory>
#include "functor.h"

//some forward declarations
struct RGBTRIPLE;
class functor;

class Request {
	//give an x and y coordinate, and memory location of "pixels"
	private:
		int pixel_x;
		int pixel_y;
		RGBTRIPLE ** pixels;

	public:
		Request(std::shared_ptr<std::mutex> r_mtx, std::shared_ptr<std::mutex> w_mtx, int x, int y, RGBTRIPLE ** rgb){
			pixel_x = x;
			pixel_y = y;
			pixels = rgb;
		}
		int CalculatePixel(){

			return 0;
		}
};


#endif /* REQUEST_H_ */
