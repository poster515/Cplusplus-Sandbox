/*
 * geometry.h
 *
 *  Created on: May 18, 2020
 *      Author: Jpost
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <math.h>

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
	//copy constructor
	Point(const Point &p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}

	//rvalue based assignment
	Point& operator=(Point &&A){
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;
		return *this;
	}

	Point& operator=(const Point &A){
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;
		return *this;
	}

	//overloaded subtraction operator;
	Point operator- (const Point &A){
		Point temp;
		temp.x = this->x - A.x;
		temp.y = this->y - A.y;
		temp.z = this->z - A.z;
		return temp;
	}
	//overloaded subtraction operator;
	Point operator+ (const Point &A){
		Point temp;
		temp.x = this->x + A.x;
		temp.y = this->y + A.y;
		temp.z = this->z + A.z;
		return temp;
	}
};

//structure to represent a difference vector between two points
//i.e., a directional vector or "ray"
//represents R = A<i> + B<j> + C<k>
struct Ray{
	float A;
	float B;
	float C;

	//normal/default constructor
	Ray(float _A = 0, float _B = 0, float _C = 0){
		this->A = _A;
		this->B = _B;
		this->C = _C;
	}
	//rvalue Point-based constructor
	Ray(Point&& A){
		this->A = (float)A.x;
		this->B = (float)A.y;
		this->C = (float)A.z;
	}

	//rvalue Ray-based constructor
	Ray(Ray&& R){
		this->A = R.A;
		this->B = R.B;
		this->C = R.C;
	}

	//move assignment/type conversion
	Ray& operator=(Point&& A){
		this->A = (float)A.x;
		this->B = (float)A.y;
		this->C = (float)A.z;
		return *this;
	}

//	Ray& operator=(Ray&& R){
//		this->A = R.A;
//		this->B = R.B;
//		this->C = R.C;
//		return *this;
//	}
	Ray& operator=(const Ray &R){
		this->A = R.A;
		this->B = R.B;
		this->C = R.C;
		return *this;
	}

	Ray operator/(float denom){
		Ray temp;
		temp.A = this->A / denom;
		temp.B = this->B / denom;
		temp.C = this->C / denom;
		return temp;
	}
	Point operator*(float mag){
		Point temp;
		temp.x = this->A * mag;
		temp.y = this->B * mag;
		temp.z = this->C * mag;
		return temp;
	}
	float dot(const Ray &r2){
		float temp((this->A * r2.A) + (this->B * r2.B) + (this->C * r2.C));
		return temp;
	}

	//compute the cosine of the angle between two rays
	float cos_theta(const Ray &r2){
		//compute magnitudes of both rays
		float mag1(std::sqrt(std::pow(this->A, 2.0) + std::pow(this->B, 2.0) + std::pow(this->C, 2.0)));
		float mag2(std::sqrt(std::pow(r2.A, 2.0) + std::pow(r2.B, 2.0) + std::pow(r2.C, 2.0)));

		//now find cos(theta) by dividing dot product by product of magnitudes
		float temp((this->dot(r2))/(mag1*mag2));
		return temp;
	}

};




#endif /* GEOMETRY_H_ */
