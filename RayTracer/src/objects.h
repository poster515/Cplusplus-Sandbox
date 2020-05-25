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
		float radius;
		Point center;
		RGBTRIPLE my_color;
		int id;

	public:

		Object(eObjectTypes eOT=eUnknown, int x=1, int y=1, int z=1, float r=1.0, uint8_t R=0x00, uint8_t G=0x00, uint8_t B=0x00, int ID=0){
			my_type = eOT;
			epsilon = 0.0001; //will probably need to tweak
			center.x = x;
			center.y = y;
			center.z = z;
			radius = r;
			my_color.rgbtRed = R; //default color is black
			my_color.rgbtGreen = G;
			my_color.rgbtBlue = B;
			id = ID;
		}
		Object& operator=(const Object &o){
			my_type = o.my_type;
			epsilon = o.epsilon;
			center = o.center;
			radius = o.radius;
			my_color = o.my_color;
			id = o.id;
			return *this;
		}

		void Intersect(Ray &primRay, Point &pHit, Ray &nHitDir, float &minDist, Object &minObject, Point &primRayOrigin){
			//basically determine whether primary ray falls within radius of object
			//need to determine if primary ray hits this object, and if so, whether it is closer than
			//current closest object

			//inputs:

			//Point *pixel: 		Point (i.e., pixel) that we're writing to (address of Request's pixel)
			//Point &pHit: 			Point where ray hits object, if applicable
			//Ray &nHitDir:			unit ray that is normal to object, where primary ray hits this object
			//float &minDist: 		current magnitude of distance to closest object
			//Object &minObject: 	current closest object
			//Point &primRayOrigin:	origin of primary ray.

			// first, compute primary ray and directional vector
			float PR_mag(std::sqrt(std::pow(primRay.A, 2.0) + std::pow(primRay.B, 2.0) + std::pow(primRay.C, 2.0)));
			Ray primRay_dir(primRay / PR_mag);

			//next, ray from eye to object and directional vector
			Ray E2O(center - primRayOrigin);
			float E2O_mag(std::sqrt(std::pow(E2O.A, 2.0) + std::pow(E2O.B, 2.0) + std::pow(E2O.C, 2.0)));
			Ray E2O_dir(E2O / E2O_mag);

			//determine cosine of angle between eye-to-pixel and eye-to-center rays
			float cos_theta(primRay_dir.dot(E2O_dir));

			//now compute right-angle length between primary ray and eye-to-object
			float RAR_sine(E2O_mag * std::sqrt(1 - std::pow(cos_theta, 2.0)));

			//also compute the corresponding length of ray that makes right angle with "length"
			float RAR_cosine(E2O_mag * cos_theta);

			//compute distance from right-angle-ray to the edge of the sphere, only if it hits the sphere
			float RAR_sine_to_sph_edge = 0.0;
			if (RAR_sine < radius){
				RAR_sine_to_sph_edge = std::sqrt(std::pow(radius,2.0) - std::pow(RAR_sine, 2.0));
			}

			switch(my_type){
				case(eSphere):
					if (RAR_sine <= radius){
						//then we're inside the sphere somewhere
						if ((RAR_cosine - RAR_sine_to_sph_edge) < minDist){
							minDist = E2O_mag*cos_theta;
							minObject = *this;
							pHit = (primRay_dir * (RAR_cosine - RAR_sine_to_sph_edge)) - primRayOrigin;

							//now compute unit directional vector normal to the surface
							Ray nHit(pHit - center);
							float nHit_mag(std::sqrt(std::pow(nHit.A, 2.0) + std::pow(nHit.B, 2.0) + std::pow(nHit.C, 2.0)));
							nHitDir = nHit / nHit_mag;
						}
					} else {
						//then we don't have a hit on this object
					}

					break;
				case(eCube):
					//calculate distance to Point p using Cartesian equation

					break;
				case(eUnknown):
					//give some default distance

					break;
			}

		}

		eObjectTypes getMyType(){
			return my_type;
		}

		RGBTRIPLE getMyColor(){
			return my_color;
		}

		int getMyID(){
			return id;
		}
};

#endif /* OBJECTS_H_ */
