/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "rgb.h"

//#define __N_ALGO__

//structure to represent a difference vector between two points
//i.e., a directional vector or "ray"
//represents R = A<i> + B<j> + C<k>
struct Point;
struct Ray{
	int x;
	int y;
	int z;
};

//structure to represent simple point in space
struct Point{
	int x;
	int y;
	int z;

	//overloading the subtraction operator
	Ray operator-(Point A){
		Ray temp;
		temp.x = this->x - A.x;
		temp.y = this->y - A.y;
		temp.z = this->z - A.z;
		return temp;
	}

	//normal constructor
	Point(int x, int y, int z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//overloading move assignment operator
	Point& operator=(Point&& point){

		// Self-assignment detection
		if (&point == this)
			return *this;

		// Transfer ownership of a.m_ptr to m_ptr
		x = point.x;
		y = point.y;
		z = point.z;

		return *this;
	}
};

class functor {
	private:
		Point * eye_position;

		void computePrimRay(int pixel_x, int pixel_y, Ray &primRay){
			Point pixel(pixel_x, pixel_y, 0);
			//subtract two points to create "ray"
			primRay = pixel - *eye_position;
		}

	public:
		functor(int image_width, int image_height, Point *eye_position){
			//just copy pointer to request's eye_position
			this->eye_position = eye_position;
		}

		RGBTRIPLE * operator()(int x, int y){

			#ifdef __N_ALGO__
				// compute primary ray direction
				Ray primRay;
				computePrimRay(x, y, primRay);

				// shoot prim ray in the scene and search for intersection
				Point pHit;
				Ray nHit;
				float minDist = std::numeric_limits<float>::infinity();

				Object object = NULL;
				for (int k = 0; k < objects.size(); ++k) {
					if (Intersect(objects[k], primRay, &pHit, &nHit)) {
						float distance = Distance(eyePosition, pHit);
						if (distance < minDistance) {
							object = objects[k];
							minDistance = distance; // update min distance
						}
					}
				}
				if (object != NULL) {
					// compute illumination
					Ray shadowRay;
					shadowRay.direction = lightPosition - pHit;
					bool isShadow = false;
					for (int k = 0; k < objects.size(); ++k) {
						if (Intersect(objects[k], shadowRay)) {
							isInShadow = true;
							break;
						}
					}
				}
				if (!isInShadow)
					pixels[i][j] = object->color * light.brightness;
				else
					pixels[i][j] = 0;
			#else
				RGBTRIPLE *rgb = new RGBTRIPLE;
				uint8_t temp = (x + y) % 256;
				rgb->rgbtRed = temp;
				rgb->rgbtGreen = temp;
				rgb->rgbtBlue = temp;
				return rgb;
			#endif
		}
};



#endif /* FUNCTOR_H_ */
