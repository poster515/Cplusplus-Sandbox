/*
 * bmpwrtr.h
 *
 *  Created on: May 4, 2020
 *      Author: Jpost
 */

#ifndef BMPWRTR_H_
#define BMPWRTR_H_

#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "bmp.h"

class BitMapWriter {
	private:

		BITMAPFILEHEADER bf;
		BITMAPINFOHEADER bi;

		RGBTRIPLE **pixels; // actual pixel data
		int row_padding; //number of bytes to pad at end of each row

		void initialize_pixels(int, int, short int);

	public:

		void waitAndWriteFile();

		BitMapWriter(int xdim_in_pixels, int ydim_in_pixels, short int bitsPerPixel, std::shared_ptr<RGBTRIPLE**> pixels_location){
			pixels = *pixels_location; //need to dereference shared_ptr here

			int temp_bytes_per_row = xdim_in_pixels * (bitsPerPixel / 8); //NOTE THIS DOES NOT WORK FOR bpp < 8
			row_padding = ((4 - (temp_bytes_per_row % 4)) % 4);
			std::cout << "Padding = " << row_padding << std::endl;

			bf.bfType = 0x4D42; //i.e., 0x4D42 or "BM": 'B' = 0x42, 'M' = 0x4D
			bf.bfSize = 54 + ((temp_bytes_per_row + row_padding) * ydim_in_pixels); //0x02 The size, in bytes, of the bitmap file.
			bf.bfReserved1 = 0; //0x06
			bf.bfReserved2 = 0; //0x08
			bf.bfOffBits = 54;  //0x0A The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.

			std::cout << "Filesize = " << bf.bfSize << " bytes" << std::endl;
			std::cout << "PixelDataOffset = " << bf.bfOffBits << std::endl;


			bi.biSize = 40;		//40d, header is 40 bytes long
			bi.biWidth = xdim_in_pixels;	//represents width of final image in 'pixels'
			bi.biHeight = ydim_in_pixels;	//represents height of final image in 'pixels'
			bi.biPlanes = 1;				// i.e., '1'
			bi.biBitCount = bitsPerPixel;
			bi.biCompression = 0;	//not using compression
			bi.biSizeImage = 0;		//since no compression is used, set to 0
			bi.biXPelsPerMeter = 0; //no preference
			bi.biYPelsPerMeter = 0; //no preference
			bi.biClrUsed = 0;		//all colors
			bi.biClrImportant = 0; 	//all colors (i.e., no preference)

			initialize_pixels(xdim_in_pixels, ydim_in_pixels, bitsPerPixel);
		}
		~BitMapWriter(){
			for (int i = 0; i < bi.biHeight; ++i){
				delete[] pixels[i];
			}
			delete[] pixels;
		}


};

void BitMapWriter::initialize_pixels(int x_dim, int y_dim, short int bitsPerPixel){
	pixels = new RGBTRIPLE*[y_dim];

	int fraction = std::max(1, 256 / (this->bi.biHeight * this->bi.biWidth));
	for (int i = 0; i < y_dim; i++){

		*(pixels + i) = new RGBTRIPLE[x_dim];
		for(int j = 0; j < x_dim; j++){

			uint8_t temp = ((fraction*i) + (fraction*j)) % 256;

			pixels[i][j].rgbtRed = temp;
			pixels[i][j].rgbtGreen = temp;
			pixels[i][j].rgbtBlue = temp;

			std::cout << "RGB at row i: " << i << ", col j: " << j << " = " << (int)temp << std::endl;
		}
	}
}

void BitMapWriter::waitAndWriteFile(){
	// PATH for files: "C:\\Users\\Jpost\\eclipse-workspace\\dsp_test"
	std::ofstream new_file;
	new_file.open("test.bmp", std::ios::out);

	//write all file and info header data
	new_file.write((const char*)&bf, sizeof(bf));
	new_file.write((const char*)&bi, sizeof(bi));

	int total_bytes = 0;
	uint8_t zero = 0;

	//now write main body of file
	for(int i = 0; i < bi.biHeight; i++){
		for(int j = 0; j < bi.biWidth; j++){
			new_file.write((const char*)&pixels[i][j], sizeof(RGBTRIPLE));
			total_bytes += sizeof(RGBTRIPLE);
			std::cout << "total data bytes written: " << total_bytes << std::endl;
		}
		//need to ensure that padding is correct, add single byte a total of row_padding times

		for(int j = 0; j < row_padding; ++j){
			new_file.write((const char*)&zero, sizeof(BYTE));
			total_bytes += sizeof(BYTE);
			std::cout << "adding extra byte. total data bytes written: " << total_bytes << std::endl;
		}
	}
	new_file.close();
	std::cout <<"done writing, total written = " << sizeof(bf) + sizeof(bi) + total_bytes<< std::endl;
}


#endif /* BMPWRTR_H_ */
