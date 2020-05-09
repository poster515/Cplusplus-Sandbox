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
#include "request.h"
#include "worker.h"

//forward declare this structure
struct RGBTRIPLE;

//need to forward declare Request for Worker class
class Request;

class Dispatcher {
	private:
		std::queue<Worker *> workers;
		std::queue<Request *> requests;
		std::vector<std::thread> threads;

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
				//create new worker
				Worker * new_worker = new Worker(requests, worker_mtx_ptr, request_mtx_ptr);
				//add worker to workers queue
				workers.push(new_worker);
				//now create new thread that runs worker's Run() function, and and add thread to vector
				std::thread thread(&Worker::Run, &new_worker);
				threads.push_back(thread);
			}
		}
		~Dispatcher(){
			//join and destroy all worker threads
			for(auto it = threads.begin(); it != threads.end(); ++it){
				(*it).join();
			}

		}

		static void addRequest(Request * request){
			worker_mutex.lock();
			if (!workers.empty()){
				workers.front()->addRequest(request);
				workers.pop();
				worker_mutex.unlock();
			} else {
				worker_mutex.unlock();
				request_mutex.lock();
				requests.push(request);
				request_mutex.unlock();
			}
		}

		static bool addWorker(Worker * worker){
			// returns true if the worker is added to worker_queue
			request_mutex.lock();
			if (!requests.empty()){
				//then we have requests that can be handled, assign one to this worker
				worker->addRequest(requests.front());
				//and then remove that request from queue
				requests.pop();
				request_mutex.unlock();
			} else {
				request_mutex.unlock();
				worker_mutex.lock();
				workers.push(worker);
				worker_mutex.unlock();
			}

			return false;
		}

		static void stop_threads(){
			//set all worker threads from waiting (for new requests) to not waiting

		}
};



#endif /* DISPATCHER_H_ */
