/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "rgb.h"
#include "objects.h"

#define __N_ALGO__

//structure to represent simple point in space
struct Point{
	int x;
	int y;
	int z;

	//normal constructor (handles empty and assigned constructors)
	Point(int x = 0, int y = 0, int z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//overloaded subtraction operator;
	Point operator- (Point &A){
		Point temp;
		temp.x = this->x - A.x;
		temp.y = this->y - A.y;
		temp.z = this->z - A.z;
		return temp;
	}
};

//structure to represent a difference vector between two points
//i.e., a directional vector or "ray"
//represents R = A<i> + B<j> + C<k>
struct Ray{
	int x;
	int y;
	int z;

	//normal/default constructor
	Ray(int x = 0, int y = 0, int z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//move assignment/type conversion
	Ray& operator=(Point&& A){
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;

		return *this;
	}
};

class functor {
	private:
		Point * eye_position;
		Point * pixel;

		void computePrimRay(int pixel_x, int pixel_y, Ray &primRay){
			//subtract two points to create "ray"
			primRay = (*pixel - *eye_position);
		}

	public:
		functor(int image_width, int image_height, Point *eye_position, Point *pixel){
			//just copy pointer to request's eye_position
			this->eye_position = eye_position;
			this->pixel = pixel;
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
//
//				Object object = NULL;
//				for (int k = 0; k < objects.size(); ++k) {
//					if (Intersect(objects[k], primRay, &pHit, &nHit)) {
//						float distance = Distance(eyePosition, pHit);
//						if (distance < minDistance) {
//							object = objects[k];
//							minDistance = distance; // update min distance
//						}
//					}
//				}
//				if (object != NULL) {
//					// compute illumination
//					Ray shadowRay;
//					shadowRay.direction = lightPosition - pHit;
//					bool isShadow = false;
//					for (int k = 0; k < objects.size(); ++k) {
//						if (Intersect(objects[k], shadowRay)) {
//							isInShadow = true;
//							break;
//						}
//					}
//				}
//				if (!isInShadow)
//					pixels[i][j] = object->color * light.brightness;
//				else
//					pixels[i][j] = 0;

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
