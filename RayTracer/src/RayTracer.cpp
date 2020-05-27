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

#define parallel

using namespace std;

int main() {

	//each pixel will be: | R (8 bits) | G (8 bits) | B (8 bits) |
	RGBTRIPLE **pixels;
	std::shared_ptr<RGBTRIPLE **> pixels_ptr(&pixels);

	auto start = std::chrono::high_resolution_clock::now();
	std::mutex pixels_mtx;
	std::shared_ptr<std::mutex> pixels_mtx_ptr(&pixels_mtx);

	#ifdef parallel
	std::mutex cout_mtx;
	std::shared_ptr<std::mutex> cout_mtx_ptr(&cout_mtx);

	std::mutex count_mtx;
	std::shared_ptr<std::mutex> count_mtx_ptr(&count_mtx);

	// initialize worker threads
	int num_threads = 4;
	Dispatcher::init(num_threads, pixels_mtx_ptr, cout_mtx_ptr, count_mtx_ptr); //create num_threads number of workers, running in num_threads number of threads
	#endif

	//set image parameters
	const int height = 128; //in pixels
	const int width = 128;  //in pixels
	const short int bitsPerPixel = 24; //0x1800

	//initialize new BMP file
	BitMapWriter BMW(width, height, bitsPerPixel, pixels_ptr, pixels_mtx_ptr);
	pixels = BMW.initialize_pixels(width, height, bitsPerPixel);

	//create a request for each pixel in image and calculate/write each pixel
	for (int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			Request * req = new Request(i, j, pixels, Dispatcher::stdcout_mtx_ptr, pixels_mtx_ptr, width, height);
			#ifdef parallel
			Dispatcher::addRequest(req);
			#else
			(*req).CalculatePixel();
			#endif
		}
	}
	#ifdef parallel
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
	#endif
	//now write to file
	BMW.waitAndWriteFile();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Total execution time: " << duration.count() << "ms" << std::endl;
	#ifdef parallel
	//stop threads and destroy worker objects
	Dispatcher::stop_threads();
	#endif



	return 0;
}
