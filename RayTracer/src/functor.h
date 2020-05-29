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


#define clamp(value) std::min(std::max(0.0, value), 255.0)

//#define NDEBUG

class functor {
	private:
		Point eye_position;
		Point * pixel;
		std::shared_ptr<std::mutex> stdcout_mtx_ptr;

	public:
		functor(int image_width, int image_height, Point *pixel, std::shared_ptr<std::mutex> cout_mtx_ptr){
			//just copy pointer to request's eye_position
			eye_position = Point(image_width / 2, image_height / 2, -(image_width + image_height) / 2);
			this->pixel = pixel;
			stdcout_mtx_ptr = cout_mtx_ptr;
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
			Object sphere6(eSphere, 128, 64, 32, 32, 0xFF, 0x00, 0xFF, 6);
			objects.push_back(sphere6);
			Object sphere7(eSphere, 0, 64, 32, 32, 0xFE, 0x00, 0x00, 7);
			objects.push_back(sphere7);

			// shoot primary ray into scene and search for intersection
			Point pHit;
			Ray nHitDir;
			Ray primRay(*pixel - eye_position);
			Object hit_object;

			float minDist = std::numeric_limits<float>::infinity();

			for (auto object : objects) {
				//Intersect determines whether ray from eye to pixel hits this object
				//if it does, "hit_object" will be pointer to the object
				//also, "hit_object" has a private member that can be used to obtain color
				object.Intersect(primRay, pHit, nHitDir, minDist, hit_object, eye_position);
			}

			if (hit_object.getMyType() != eUnknown) {
				RGBTRIPLE color(hit_object.getMyColor());
				Point pHitCopy = pHit;
				Ray shadowRay = (light - pHitCopy);
				float cos_theta(shadowRay.cos_theta(nHitDir));

				//for debugging only, need to ensure cos_theta is valid

				assert(cos_theta >= -1 && cos_theta <= 1);

				Object shadow_object;
				Ray nHitShadowDir;
				float minDistShadow = std::numeric_limits<float>::infinity();

				for (auto object : objects) {
					//run Intersect algorithm again with new pixel and eye_position values
					object.Intersect(shadowRay, pHit, nHitShadowDir, minDistShadow, shadow_object, pHitCopy);
				}

				float shift_factor(0.0);
				if ((shadow_object.getMyType() != eUnknown) && (shadow_object.getMyID() != hit_object.getMyID())){
					shift_factor = cos_theta * 10;

				}

				rgb.rgbtRed = (uint8_t)clamp((((1.0 + cos_theta) * (float)color.rgbtRed) - shift_factor));
				rgb.rgbtGreen = (uint8_t)clamp((((1.0 + cos_theta) * (float)color.rgbtGreen) - shift_factor));
				rgb.rgbtBlue = (uint8_t)clamp((((1.0 + cos_theta) * (float)color.rgbtBlue) - shift_factor));

			} else {
				uint8_t temp = 0xFF;
				rgb.rgbtRed = temp;
				rgb.rgbtGreen = temp;
				rgb.rgbtBlue = temp;
			}

		}
};



#endif /* FUNCTOR_H_ */
