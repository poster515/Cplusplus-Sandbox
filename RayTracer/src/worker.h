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

class Request;

class Worker {
	private:
		std::queue<Request *> &requests;
		bool running;
		bool stopped;
		std::shared_ptr<std::mutex> request_mtx_ptr;
		std::shared_ptr<std::mutex> worker_mtx_ptr;

	public:
		//need to constantly be scanning Dispatcher's "requests" queue and grab one if available
		Worker(std::queue<Request *> &request_queue, std::shared_ptr<std::mutex> r_mtx, std::shared_ptr<std::mutex> w_mtx){
			//need to provide address of request queue so we know where to look for work
			requests = request_queue;
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
				//block/lock request mutex

				//check if there are any requests in request queue

					//if there are, grab and remove it (we'll already have request queue mutex at this point), and unlock requests mutex
					//block/lock worker mutex and remove this worker from queue, then unlock worker mutex

					//execute request

				//check if "stop" bool is true, and if so just return.
			}

		}
		void Stop(){

		}
};


#endif /* WORKER_H_ */
