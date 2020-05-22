//============================================================================
// Name        : RayTracer.cpp
// Author      : J Post
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "rgb.h"
#include "bmpwrtr.h"
#include "request.h"
#include "dispatcher.hpp"

#define _DEBUG_

using namespace std;

int main() {

	//each pixel will be: | R (8 bits) | G (8 bits) | B (8 bits) |
	RGBTRIPLE **pixels;
	std::shared_ptr<RGBTRIPLE **> pixels_ptr(&pixels);
	std::mutex pixels_mtx;
	std::shared_ptr<std::mutex> pixels_mtx_ptr(&pixels_mtx);

	#ifdef _DEBUG_
	std::mutex cout_mtx;
	std::shared_ptr<std::mutex> cout_mtx_ptr(&cout_mtx);
	#endif

	std::mutex count_mtx;
	std::shared_ptr<std::mutex> count_mtx_ptr(&count_mtx);

	// initialize worker threads
	int num_threads = 4;
	Dispatcher::init(num_threads, pixels_mtx_ptr, cout_mtx_ptr, count_mtx_ptr); //create num_threads number of workers, running in num_threads number of threads

	//set image parameters
	const int height = 120; //in pixels
	const int width = 120;  //in pixels
	const short int bitsPerPixel = 24; //0x1800

	//initialize new BMP file
	BitMapWriter BMW(width, height, bitsPerPixel, pixels_ptr, pixels_mtx_ptr);
	pixels = BMW.initialize_pixels(width, height, bitsPerPixel);

	//create a request for each pixel in image and calculate/write each pixel
	for (int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			Request * req = new Request(i, j, pixels, Dispatcher::stdcout_mtx_ptr, pixels_mtx_ptr, width, height);
			Dispatcher::addRequest(req);
		}
	}

	//wait for threads to have written the correct number of pixels
	while(1){

		int total_pixels = height * width;
		std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
		if (count_mtx.try_lock()){
			if(Dispatcher::count == total_pixels){
				//then we've processed all the pixel values
				count_mtx.unlock();
				break;
			}
			count_mtx.unlock();
		}

	}

	//now write to file
	BMW.waitAndWriteFile();

	//stop threads and destroy worker objects
	Dispatcher::stop_threads();


	return 0;
}
