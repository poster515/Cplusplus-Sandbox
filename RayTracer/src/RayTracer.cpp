//============================================================================
// Name        : RayTracer.cpp
// Author      : J Post
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "dispatcher.h"
#include "bmpwrtr.h"

using namespace std;

int main() {

	//want each pixel to be 24 bits, so we need a 32 bit container (e.g., int)
	//each int in pixels will be: | unused (8 bits) | R (8 bits) | G (8 bits) | B (8 bits) |
	RGBTRIPLE **pixels;
	std::shared_ptr<RGBTRIPLE**> pixels_location(&pixels);

	//create dispatcher object
	int num_threads = 4;
	Dispatcher dp(num_threads); //create num_threads number of workers, running in num_threads number of threads

	//for now, just make a simple 4x4 pixel object
	const int height = 400; //in pixels
	const int width = 300;  //in pixels
	const short int bitsPerPixel = 24; //0x1800

	//initialize new BMP file
	BitMapWriter BMW(width, height, bitsPerPixel, pixels_location);

	//create a request for each pixel in image
	for (int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			Request * req = new Request(height, width, pixels);
			dp.addRequest(req);
		}

	}
	BMW.waitAndWriteFile();

	return 0;
}
