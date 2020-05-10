//============================================================================
// Name        : RayTracer.cpp
// Author      : J Post
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

#include "rgb.h"
#include "bmpwrtr.h"
#include "request.h"
#include "dispatcher.hpp"

using namespace std;

int main() {

	//each pixel will be: | R (8 bits) | G (8 bits) | B (8 bits) |
	RGBTRIPLE **pixels;
	std::shared_ptr<RGBTRIPLE **> pixels_ptr(&pixels);
	std::mutex pixels_mtx;
	std::shared_ptr<std::mutex> pixels_mtx_ptr(&pixels_mtx);

	// initialize worker threads
	int num_threads = 4;
	Dispatcher::init(num_threads, pixels_ptr, pixels_mtx_ptr); //create num_threads number of workers, running in num_threads number of threads

	//set image parameters
	const int height = 400; //in pixels
	const int width = 300;  //in pixels
	const short int bitsPerPixel = 24; //0x1800

	//initialize new BMP file
	BitMapWriter BMW(width, height, bitsPerPixel, pixels_ptr);

	//create a request for each pixel in image and calculate/write each pixel
	for (int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			Request * req = new Request(i, j, pixels_ptr);
			Dispatcher::addRequest(req);
		}
	}
	//stop threads and write image to BMP file
	Dispatcher::stop_threads();
	BMW.waitAndWriteFile();

	return 0;
}
