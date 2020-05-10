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

class Request {
	//give an x and y coordinate, and memory location of "pixels"
	private:
		int pixel_x;
		int pixel_y;
		std::shared_ptr<RGBTRIPLE**> pixels_location;

	public:
		Request(int x, int y, std::shared_ptr<RGBTRIPLE**> pl){
			pixel_x = x;
			pixel_y = y;
			pixels_location = pl;
		}
		void CalculatePixel(std::shared_ptr<std::mutex> pixels_mtx_ptr){
			RGBTRIPLE rgb = functor()(pixel_x, pixel_y);

			std::lock_guard<std::mutex> lg(*pixels_mtx_ptr);
			(*pixels_location)[pixel_y][pixel_x].rgbtRed = rgb.rgbtRed;
			(*pixels_location)[pixel_y][pixel_x].rgbtRed = rgb.rgbtGreen;
			(*pixels_location)[pixel_y][pixel_x].rgbtRed = rgb.rgbtBlue;
		}
};


#endif /* REQUEST_H_ */
