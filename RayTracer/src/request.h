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
		int pixel_x;
		int pixel_y;
		int width;
		int height;
		RGBTRIPLE** pixels; // actual pixel data
		std::shared_ptr<std::mutex> cout_mtx_ptr;
		std::shared_ptr<std::mutex> pixels_mtx_ptr;
		Point eye_position;

	public:
		Request(int y, int x,
			RGBTRIPLE** pl,
			std::shared_ptr<std::mutex> cout_mtx_ptr,
			std::shared_ptr<std::mutex> pixels_mtx_ptr,
			const int width,
			const int height){
				pixel_x = x;
				pixel_y = y;
				pixels = pl;
				this->cout_mtx_ptr = cout_mtx_ptr;
				this->pixels_mtx_ptr = pixels_mtx_ptr;
				this->width = width;
				this->height = height;

				// set an arbitrary eye position. should make this more user-friendly.
				eye_position = Point(width / 2, height / 2, (width + height) / 2);
		}

		void CalculatePixel(){
			functor * func = new functor(width, height, &eye_position);
			RGBTRIPLE * rgb = (*func)(pixel_x, pixel_y);
			(*pixels_mtx_ptr).lock();
			pixels[pixel_y][pixel_x].rgbtRed = rgb->rgbtRed;
			pixels[pixel_y][pixel_x].rgbtGreen = rgb->rgbtGreen;
			pixels[pixel_y][pixel_x].rgbtBlue = rgb->rgbtBlue;
			(*pixels_mtx_ptr).unlock();

			delete rgb;
		}
		int get_x(){ return pixel_x; }
		int get_y(){ return pixel_y; }
};


#endif /* REQUEST_H_ */
