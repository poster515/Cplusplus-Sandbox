/*
 * objects.h
 *
 *  Created on: May 17, 2020
 *      Author: Jpost
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <math.h>

enum eObjectTypes {
	eSphere,
	eCube,
	eUnknown
};

class Object {
	private:
		eObjectTypes my_type;
		float epsilon;
		Point center;
		//for sphere this is obvious, for cubes this is the distance from center directly to edge
		float radius;
		RGBTRIPLE my_color;

	public:

		Object(eObjectTypes eOT=eUnknown, int x=0, int y=0, int z=0, float r=1.0, uint8_t R=0x00, uint8_t G=0x00, uint8_t B=0x00){
			my_type = eOT;
			epsilon = 0.0001; //will probably need to tweak
			center.x = x;
			center.y = y;
			center.z = z;
			radius = r;
			my_color.rgbtRed = R; //default color is black
			my_color.rgbtGreen = G;
			my_color.rgbtBlue = B;
		}

		void Intersect(Ray &primRay, Point * pHit, Ray * nHit, float &minDist, Object *minObject, Point &ep){
			//basically determine whether primary ray falls within radius of object
			//need to determine if primary ray hits this object, and if so, whether it is closer than
			//current closest object

			//inputs:

			//Ray &primRay: 		ray shot from eye_position to pixel
			//Point * pHit: 		point where ray hits object, if applicable
			//Ray * nHit: 			ray that is normal to object, where primary ray hits object
			//float &minDist: 		current magnitude of distance to closest object
			//Object &minObject: 	current closest object
			//Point &ep: 			eye position.

			float distance(0.0);

			//first, obtain magnitude of primary ray
			float PR_mag(std::sqrt(std::pow(primRay.A, 2.0) + std::pow(primRay.B, 2.0) + std::pow(primRay.C, 2.0)));

			//then, normalize primary ray to create directional vector
			Ray primRay_dir(primRay / PR_mag);

			//next, obtain magnitude of ray from eye to object
			Ray E2O(center - ep);
			float E2O_mag(std::sqrt(std::pow(E2O.A, 2.0) + std::pow(E2O.B, 2.0) + std::pow(E2O.C, 2.0)));

			//again, normalize eye-to-object ray to create directional vector
			Ray E2O_dir(E2O / E2O_mag);

			//determine cosine of angle between eye-to-pixel and eye-to-center rays
			float cos_theta(primRay_dir.dot(E2O_dir));

			//now compute right-angle length between primary ray and eye-to-object
			float RAR_sine(E2O_mag * std::sqrt(1 - std::pow(cos_theta, 2.0)));

			//also compute the corresponding length of ray that makes right angle with "length"
			float RAR_cosine(E2O_mag * cos_theta);

			//added epsilon to radius to ensure there are no sqrt(<0) issues
			float ROR_sine_to_sph_edge(std::sqrt(std::pow(radius+epsilon,2.0) - std::pow(RAR_sine, 2.0)));

			switch(my_type){
				case(eSphere):
					if (RAR_sine <= radius){
						//then we're inside the sphere somewhere
						if ((RAR_cosine - ROR_sine_to_sph_edge) < minDist){
							minDist = E2O_mag*cos_theta;
							minObject = this;
						}
					}

					break;
				case(eCube):
					//calculate distance to Point p using Cartesian equation
					distance = 0.0;
					break;
				case(eUnknown):
					//give some default distance
					distance = 0.0;
					break;
			}

		}

		RGBTRIPLE getMyColor(){
			return my_color;
		}
};

#endif /* OBJECTS_H_ */
