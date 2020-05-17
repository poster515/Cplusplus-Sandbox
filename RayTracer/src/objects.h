/*
 * objects.h
 *
 *  Created on: May 17, 2020
 *      Author: Jpost
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_

//file to capture various objects
//makes several different types of objects (e.g., sphere)
//with an "object" template class wrapper for each

class Sphere {
	private:
		int radius;

	public:
		Sphere(int r = 1){
			radius = r;
		}
};

class Cube {
	private:
		int width;

	public:
		Cube(int w = 1){
			width = w;
		}
};

template <class T>
class Object : public T {

};




#endif /* OBJECTS_H_ */
