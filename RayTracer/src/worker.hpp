/*
 * worker.hpp
 *
 *  Created on: May 9, 2020
 *      Author: Jpost
 */

#ifndef WORKER_HPP_
#define WORKER_HPP_
#include <chrono>

#include "worker.h"
#include "dispatcher.hpp"

void Worker::Run(){
	running = true;
	while (running){
		(*addworker_mtx_ptr).lock();
		if(Dispatcher::addWorker(this, my_req)){
			(*addworker_mtx_ptr).unlock();
			//then there are no requests, and dispatcher adds "this" to worker queue
			if(stopped){
				//we've stopped running the program and can simply return
				return;
			} else {
				//use condition variable controlled by dispatcher to let worker know it has a request to execute
				cv.wait(ulock, [&]{ return this->checkRequest(); });
				ulock.unlock();
			}
		} else {
			(*addworker_mtx_ptr).unlock();
		}

		if(my_req != nullptr){
			// call request function to calculate and store pixel data
			(*my_req).CalculatePixel();

			//now increment total_pixels calculated
			(*Dispatcher::count_mtx_ptr).lock();
			++Dispatcher::count;
			std::cout << "worker completed request. tid = "
					<< std::this_thread::get_id()
					<< ", y = " << (*my_req).get_y()
					<< ", x = " << (*my_req).get_x()
					<< ", count = " << Dispatcher::count
					<< std::endl;
			(*Dispatcher::count_mtx_ptr).unlock();

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
