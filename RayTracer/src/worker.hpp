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
		if(Dispatcher::addWorker(this, my_req)){
			//then there are no requests, and dispatcher adds "this" to worker queue
			if(stopped){
				//we've stopped running the program and can simply return
				return;
			} else {
				//use condition variable controlled by dispatcher to let worker know it has a request to execute
				(*Dispatcher::stdcout_mtx_ptr).lock();
				std::cout << "worker will now wait for new request. tid = " << std::this_thread::get_id() << std::endl;
				(*Dispatcher::stdcout_mtx_ptr).unlock();

				cv.wait(ulock, [&]{ return this->checkRequest(); });
				ulock.unlock();
			}
		}

		if(my_req != nullptr){
			(*Dispatcher::stdcout_mtx_ptr).lock();
			std::cout << "worker has new request. tid = " << std::this_thread::get_id() << std::endl;
			(*Dispatcher::stdcout_mtx_ptr).unlock();
			// call request function to calculate and store pixel data
			(*my_req).CalculatePixel(this->pixels_mtx_ptr);

			(*Dispatcher::stdcout_mtx_ptr).lock();
			std::cout << "worker has completed calc. tid = " << std::this_thread::get_id() << std::endl;
			(*Dispatcher::stdcout_mtx_ptr).unlock();
			//delete this request since it's now complete
			delete my_req;
			//reset "this->my_req" to nullptr to handle another request
			my_req = nullptr;
			//reset has_request variable
			has_request = false;
			//now increment total_pixels calculated
			(*Dispatcher::count_mtx_ptr).lock();
			++Dispatcher::count;
			(*Dispatcher::count_mtx_ptr).unlock();
		}
	}
}





#endif /* WORKER_HPP_ */
