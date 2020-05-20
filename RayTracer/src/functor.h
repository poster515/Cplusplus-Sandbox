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
		Point eye_position;
		Point * pixel;

	public:
		functor(int image_width, int image_height, Point *pixel){
			//just copy pointer to request's eye_position
			eye_position = Point(image_width / 2, image_height / 2, (image_width + image_height) / 2);
			this->pixel = pixel;
		}

		void operator()(RGBTRIPLE &rgb){

			#ifdef __N_ALGO__
				// compute primary ray direction
				Ray primRay(*pixel - eye_position);

				//this is where we define background objects
				std::vector<Object> objects;
				Object sphere1(eSphere, 2, 5, 9, 2.0, 0xFF, 0xFF, 0xFF);
				objects.push_back(sphere1);

				// shoot primary ray into scene and search for intersection
				Point pHit;
				Ray nHit;
				Object *hit_object(nullptr);
				float minDist = std::numeric_limits<float>::infinity();

				for (auto object : objects) {
					object.Intersect(primRay, &pHit, &nHit, minDist, hit_object, eye_position);
				}

				uint8_t temp = (pixel->x + pixel->y) % 256;
				rgb.rgbtRed = temp;
				rgb.rgbtGreen = temp;
				rgb.rgbtBlue = temp;

				if (hit_object != nullptr) {
					rgb = (*hit_object).getMyColor();
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
				} else {

				}
//				if (!isInShadow)
//					pixels[i][j] = object->color * light.brightness;
//				else
//					pixels[i][j] = 0;

			#endif
		}
};



#endif /* FUNCTOR_H_ */
