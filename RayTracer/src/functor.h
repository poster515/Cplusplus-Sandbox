/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include "rgb.h"
#include "geometry.h"
#include "objects.h"

#define __N_ALGO__

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
				Object object(eUnknown);
				float minDist = std::numeric_limits<float>::infinity();

				std::vector<Object> objects;
				Object sphere1(eSphere);
				objects.push_back(sphere1);

				for (unsigned int k = 0; k < objects.size(); ++k) {
					if (objects[k].Intersect(primRay, &pHit, &nHit)) {
						float distance = objects[k].Proximity(eye_position, &pHit);
						if (distance < minDist) {
							object = objects[k];
							minDist = distance; // update min distance
						}
					}
				}

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
