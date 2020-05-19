/*
 * objects.h
 *
 *  Created on: May 17, 2020
 *      Author: Jpost
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_

enum eObjectTypes {
	eSphere,
	eCube,
	eUnknown
};

class Object {
	private:
		eObjectTypes my_type;
		float epsilon;


	public:

		Object(eObjectTypes eOT){
			my_type = eOT;
			epsilon = 0.0001; //will probably need to tweak
		}

		float Proximity(Point * eye, Point * p){
			float distance(0.0);

			switch(my_type){
				case(eSphere):
					//calculate distance to Point p using spherical equation
					distance = 0.0;
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

			return distance;
		}
		bool Intersect(Ray primRay, Point * pHit, Ray * nHit){

			return false;
		}
};

#endif /* OBJECTS_H_ */
