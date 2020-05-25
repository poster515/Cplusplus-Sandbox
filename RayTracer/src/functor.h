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

class functor {
	private:
		Point eye_position;
		Point * pixel;

	public:
		functor(int image_width, int image_height, Point *pixel){
			//just copy pointer to request's eye_position
			eye_position = Point(image_width / 2, image_height / 2, -(image_width + image_height) / 2);
			this->pixel = pixel;
		}

		void operator()(RGBTRIPLE &rgb){
			//define position of uniform light source
			Point light(0, 60, 45);

			//this is where we define background objects
			std::vector<Object> objects;
			Object sphere1(eSphere, 70, 90, 45, 50, 0x7F, 0x7F, 0x7F);
			objects.push_back(sphere1);
			Object sphere2(eSphere, 90, 90, 20, 30, 0xFF, 0x00, 0x00);
			objects.push_back(sphere2);
			Object sphere3(eSphere, 30, 30, 90, 30, 0x00, 0xFF, 0x00);
			objects.push_back(sphere3);

			// shoot primary ray into scene and search for intersection
			Point pHit;
			Ray nHit;
			Object hit_object;
			Object shadow_object;
			float minDist = std::numeric_limits<float>::infinity();

			for (auto object : objects) {
				//Intersect determines whether ray from eye to pixel hits this object
				//if it does, "hit_object" will be pointer to the object
				//also, "hit_object" has a private member that can be used to obtain color
				object.Intersect(pixel, pHit, nHit, minDist, hit_object, eye_position);
			}

			if (hit_object.getMyType() != eUnknown) {
				rgb = hit_object.getMyColor();
				// compute illumination
				Ray shadowRay(light - pHit);

				float cos_theta(shadowRay.cos_theta(nHit));
				bool isInShadow = false;

				if ((cos_theta < 0) && (cos_theta >= -1)){
					//then we're in a shadow
					isInShadow = true;
				} else {
					//not in the shadow of the hit object
					//determine if any other objects are between light and hit object
					for (auto object: objects) {
						//run Intersect algorithm again with new pixel and eye_position values
						object.Intersect(pixel, pHit, nHit, minDist, hit_object, eye_position);
						if (/* hit_object != object */) {
							isInShadow = true;
							break;
						}
					}
				}

			} else {
				uint8_t temp = 0xFF;
				rgb.rgbtRed = temp;
				rgb.rgbtGreen = temp;
				rgb.rgbtBlue = temp;

			}
//			if (!isInShadow)
//				pixels[i][j] = object->color * light.brightness;
//			else
//				pixels[i][j] = 0;

		}
};



#endif /* FUNCTOR_H_ */
