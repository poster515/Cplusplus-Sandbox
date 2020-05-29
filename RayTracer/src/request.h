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
#include <thread>
#include "functor.h"

class Request {
	//give an x and y coordinate, and memory location of "pixels"
	private:
		int width;
		int height;
		RGBTRIPLE** pixels; // actual pixel data pointer
		std::shared_ptr<std::mutex> cout_mtx_ptr; //for debug purposes
		std::shared_ptr<std::mutex> pixels_mtx_ptr;
		Point pixel;

	public:
		Request(int y, int x,
			RGBTRIPLE** pl,
			std::shared_ptr<std::mutex> cout_mtx_ptr,
			std::shared_ptr<std::mutex> pixels_mtx_ptr,
			const int width,
			const int height){
				pixels = pl;
				this->cout_mtx_ptr = cout_mtx_ptr;
				this->pixels_mtx_ptr = pixels_mtx_ptr;
				this->width = width;
				this->height = height;
				pixel = Point(x, y, 0);
		}

		void CalculatePixel(){
			functor func1(width, height, &pixel, cout_mtx_ptr);
			RGBTRIPLE rgb;
			func1(rgb);
			(*pixels_mtx_ptr).lock();
			pixels[pixel.y][pixel.x] = rgb;
			(*pixels_mtx_ptr).unlock();
		}
		int get_x(){ return pixel.x; }
		int get_y(){ return pixel.y; }
};


#endif /* REQUEST_H_ */
