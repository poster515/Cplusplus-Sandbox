/*
 * worker.h
 *
 *  Created on: May 7, 2020
 *      Author: Jpost
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <mutex>
#include <thread>
#include <queue>
#include <memory>
#include "dispatcher.h"

class Request;

class Worker {
	private:
		bool running;
		bool stopped;
		std::shared_ptr<std::mutex> request_mtx_ptr;
		std::shared_ptr<std::mutex> worker_mtx_ptr;

	public:
		Worker(std::shared_ptr<std::mutex> r_mtx, std::shared_ptr<std::mutex> w_mtx){
			running = false;
			stopped = false;
			request_mtx_ptr = r_mtx;
			worker_mtx_ptr = w_mtx;
		}
		~Worker(){

		}
		void Run(){
			running = true;
			while (running){
				if(Dispatcher::addWorker(this)){
					//then there are no requests, and dispatcher adds "this" to worker queue
				}
				//block/lock request mutex

				//check if there are any requests in request queue

					//if there are, grab and remove it (we'll already have request queue mutex at this point), and unlock requests mutex
					//block/lock worker mutex and remove this worker from queue, then unlock worker mutex

					//execute request

				//check if "stop" bool is true, and if so just return.

			}

		}
		void addRequest(Request *req){

		}
		void Stop(){

		}
};


#endif /* WORKER_H_ */
