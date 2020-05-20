/*
 * geometry.h
 *
 *  Created on: May 18, 2020
 *      Author: Jpost
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_


//structure to represent simple point in space
struct Point{
	int x;
	int y;
	int z;

	//normal constructor (handles empty and assigned constructors)
	Point(int x = 0, int y = 0, int z = 0){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//overloaded subtraction operator;
	Point operator- (Point &A){
		Point temp;
		temp.x = this->x - A.x;
		temp.y = this->y - A.y;
		temp.z = this->z - A.z;
		return temp;
	}
};

//structure to represent a difference vector between two points
//i.e., a directional vector or "ray"
//represents R = A<i> + B<j> + C<k>
struct Ray{
	int A;
	int B;
	int C;

	//normal/default constructor
	Ray(int _A = 0, int _B = 0, int _C = 0){
		this->A = _A;
		this->B = _B;
		this->C = _C;
	}
	//rvalue Point-based constructor
	Ray(Point&& A){
		this->A = A.x;
		this->B = A.y;
		this->C = A.z;
	}

	//rvalue Ray-based constructor
	Ray(Ray&& R){
		this->A = R.A;
		this->B = R.B;
		this->C = R.C;
	}

	//move assignment/type conversion
	Ray& operator=(Point&& A){
		this->A = A.x;
		this->B = A.y;
		this->C = A.z;
		return *this;
	}
	Ray operator/(float denom){
		Ray temp;
		temp.A /= denom;
		temp.B /= denom;
		temp.C /= denom;
		return temp;
	}
	float dot(Ray &r2){
		float temp;
		temp = (this->A * r2.A) + (this->B * r2.B) + (this->C * r2.C);
		return temp;
	}
};




#endif /* GEOMETRY_H_ */
