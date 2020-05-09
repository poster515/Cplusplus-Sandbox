/*
 * worker.hpp
 *
 *  Created on: May 9, 2020
 *      Author: Jpost
 */

#ifndef WORKER_HPP_
#define WORKER_HPP_

#include "worker.h"
#include "dispatcher.h"

void Worker::Run(){
	running = true;
	while (running){
		if(Dispatcher::addWorker(this, my_req)){
			//then there are no requests, and dispatcher adds "this" to worker queue
			if(stopped){
				//we've stopped running the program and can simply return
				return;
			} else {
				//use condition variable controlled by dispatcher to let worker know it has a request to execute
				std::unique_lock<std::mutex> ulock(*pixels_mtx_ptr);
				cv.wait(ulock, []{ return checkRequest(); });
				ulock.unlock();
				ulock.release();
			}
		}

		if(my_req != nullptr){
			// call request function to calculate and store pixel data
			(*my_req).CalculatePixel(this->pixels_mtx_ptr);
			//delete this request since it's now complete
			delete my_req;
			//reset "this->my_req" to nullptr to handle another request
			my_req = nullptr;
			//reset has_request variable
			has_request = false;
		}
	}
}





#endif /* WORKER_HPP_ */
