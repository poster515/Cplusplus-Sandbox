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
			Point light(640, 1000, 320);

			//this is where we define background objects
			std::vector<Object> objects;

			Object sphere4(eSphere, 640, 0, 320, 320, 0x00, 0xFF, 0x00, 4);
			objects.push_back(sphere4);
			Object sphere5(eSphere, 640, 640, 320, 160, 0x00, 0x00, 0xFF, 5);
			objects.push_back(sphere5);
			Object sphere6(eSphere, 1280, 640, 320, 320, 0xFF, 0x00, 0xFF, 6);
			objects.push_back(sphere6);
			Object sphere7(eSphere, 0, 640, 320, 320, 0xFF, 0x00, 0x00, 7);
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
				Point pHitShadow;
				Ray nHitShadowDir;
				float minDistShadow = std::numeric_limits<float>::infinity();

				for (auto object : objects) {
					//run Intersect algorithm again with new pixel and eye_position values
					if (object.getMyID() != hit_object.getMyID()){
						object.ShadowIntersect(shadowRay, pHitShadow, nHitShadowDir, minDistShadow, shadow_object, pHitCopy);
					}
				}

				float shift_factor(1.0);
				if (shadow_object.getMyType() != eUnknown){
					//compute ray to shadow object center, and angle to original pHit
					Ray pHit_to_shadow_obj_cent(shadow_object.getMyCenter() - pHit);
					float cos_theta2(nHitDir.cos_theta(pHit_to_shadow_obj_cent));

					if ((cos_theta >= 0) || (cos_theta <= cos_theta2)){
						shift_factor = 0.60;
					}
				}

				rgb.rgbtRed = (uint8_t)(shift_factor * clamp((1.0 + (cos_theta*shift_factor)) * (float)color.rgbtRed / 2.0));
				rgb.rgbtGreen = (uint8_t)(shift_factor * clamp((1.0 + (cos_theta*shift_factor)) * (float)color.rgbtGreen / 2.0));
				rgb.rgbtBlue = (uint8_t)(shift_factor * clamp((1.0 + (cos_theta*shift_factor)) * (float)color.rgbtBlue / 2.0));

			} else {
				uint8_t temp = 0xFF;
				rgb.rgbtRed = temp;
				rgb.rgbtGreen = temp;
				rgb.rgbtBlue = temp;
			}

		}
};



#endif /* FUNCTOR_H_ */
