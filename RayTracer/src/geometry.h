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
	Ray operator/(float denom){
		Ray temp;
		temp.A = this->A / denom;
		temp.B = this->B / denom;
		temp.C = this->C / denom;
		return temp;
	}
	float dot(Ray &r2){
		float temp;
		temp = (this->A * r2.A) + (this->B * r2.B) + (this->C * r2.C);
		return temp;
	}
};




#endif /* GEOMETRY_H_ */
