/*
 * dispatcher.h
 *
 *  Created on: May 6, 2020
 *      Author: Jpost
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <mutex>
#include <thread>
#include <queue>
#include <memory>

#include "worker.h"

//forward declare this structure
struct RGBTRIPLE;

//need to forward declare Request for Worker class
class Request;

class Dispatcher {
	private:
		std::queue<Worker *> workers;
		std::queue<Request *> requests;

		std::mutex worker_mutex;
		std::shared_ptr<std::mutex> worker_mtx_ptr;
		std::mutex request_mutex;
		std::shared_ptr<std::mutex> request_mtx_ptr;

	public:
		Dispatcher(int num_threads){
			//initialize shared_ptrs
			worker_mtx_ptr((std::shared_ptr<std::mutex>) &worker_mutex);
			request_mtx_ptr((std::shared_ptr<std::mutex>) &request_mtx_ptr);

			//create a num_threads number of workers
			for(int i = 0; i < num_threads; ++i){
				Worker * new_worker = new Worker(requests, worker_mtx_ptr, request_mtx_ptr);
				workers.push(new_worker);
			}
		}
		~Dispatcher(){
			//join and destroy all worker threads

		}

		void addRequesttoQueue(int x, int y, RGBTRIPLE **pixels){
			//initialize new request

			//add to queue

		}

		void stop_threads(){
			//set all worker threads from waiting (for new requests) to not waiting

		}
};



#endif /* DISPATCHER_H_ */
