/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

#include <cassert>
#include <algorithm>

#include "rgb.h"
#include "geometry.h"
#include "objects.h"

#define clamp(value) std::min(std::max(0, value), 255)

//#define NDEBUG

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
			Point light(64, 100, 32);

			//this is where we define background objects
			std::vector<Object> objects;
//			Object sphere1(eSphere, 70, 90, 45, 50, 0x00, 0x00, 0x7F, 1);
//			objects.push_back(sphere1);
//			Object sphere2(eSphere, 90, 90, 20, 30, 0xFF, 0x00, 0x00, 2);
//			objects.push_back(sphere2);
//			Object sphere3(eSphere, 30, 30, 90, 30, 0x00, 0xFF, 0x00, 3);
//			objects.push_back(sphere3);
			Object sphere4(eSphere, 64, 0, 32, 32, 0x00, 0xFF, 0x00, 4);
			objects.push_back(sphere4);
			Object sphere5(eSphere, 64, 64, 32, 16, 0x00, 0x00, 0xFF, 5);
			objects.push_back(sphere5);

			// shoot primary ray into scene and search for intersection
			Point pHit;
			Ray nHitDir;
			Ray primRay(*pixel - eye_position);
			Object hit_object;
			Object shadow_object;
			float minDist = std::numeric_limits<float>::infinity();

			for (auto object : objects) {
				//Intersect determines whether ray from eye to pixel hits this object
				//if it does, "hit_object" will be pointer to the object
				//also, "hit_object" has a private member that can be used to obtain color
				object.Intersect(primRay, pHit, nHitDir, minDist, hit_object, eye_position);
			}

			if (hit_object.getMyType() != eUnknown) {

				Ray shadowRay(light - pHit);
				float cos_theta(shadowRay.cos_theta(nHitDir));

				//for debugging only, need to ensure cos_theta is valid
				assert(cos_theta >= -1 && cos_theta <= 1);

				// first check if we're on the "sunny side" of the object
				if (cos_theta > 0){
					//determine if any other objects are between light and hit object
					primRay = (light - pHit);
					minDist = std::numeric_limits<float>::infinity();
					for (auto object : objects) {
						//run Intersect algorithm again with new pixel and eye_position values
						object.Intersect(primRay, pHit, nHitDir, minDist, shadow_object, pHit);
					}
				}
				RGBTRIPLE color = hit_object.getMyColor();

				if (shadow_object.getMyType() != eUnknown){
					//then we're in a shadow
					//right shift by one to divide by 2
					float light_scale_R(color.rgbtRed >> 1);
					float light_scale_G(color.rgbtGreen >> 1);
					float light_scale_B(color.rgbtBlue >> 1);

					rgb.rgbtRed = (cos_theta + 1.0) * light_scale_R;
					rgb.rgbtGreen = (cos_theta + 1.0) * light_scale_G;
					rgb.rgbtBlue = (cos_theta + 1.0) * light_scale_B;
				} else {
					//not in any other object's shadow.
					//use a linear scale, based on angle between primary ray and pHit to light
					float offset(255);
					float light_scale_R(offset-color.rgbtRed);
					float light_scale_G(offset-color.rgbtGreen);
					float light_scale_B(offset-color.rgbtBlue);

					rgb.rgbtRed = (uint8_t)((int)color.rgbtRed + (int)(cos_theta * light_scale_R));
					rgb.rgbtGreen = (uint8_t)((int)color.rgbtGreen + (int)(cos_theta * light_scale_G));
					rgb.rgbtBlue = (uint8_t)((int)color.rgbtBlue + (int)(cos_theta * light_scale_B));

				}
				return;
			} else {
				uint8_t temp = 0xFF;
				rgb.rgbtRed = temp;
				rgb.rgbtGreen = temp;
				rgb.rgbtBlue = temp;
				return;
			}
		}
};



#endif /* FUNCTOR_H_ */
