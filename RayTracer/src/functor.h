/*
 * functor.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef FUNCTOR_H_
#define FUNCTOR_H_

class functor {

	public:
		int operator()(int x, int y){
			int local_x = x;
			int local_y = y;

			return pixelCalc(local_x, local_y);
		}

		int pixelCalc(int x, int y){
			//THIS IS THE BREAD AND BUTTER
			return 0;
		}
};



#endif /* FUNCTOR_H_ */
