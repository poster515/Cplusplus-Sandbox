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
#include <condition_variable>
#include "worker.h"

class Dispatcher {
	private:
		static std::queue<Worker *> workers;
		static std::queue<Request *> requests;
		static std::vector<std::thread *> threads;

		static std::mutex worker_mutex;
		static std::shared_ptr<std::mutex> worker_mtx_ptr;
		static std::mutex request_mutex;
		static std::shared_ptr<std::mutex> request_mtx_ptr;

		static std::condition_variable cv;

	public:
		Dispatcher(int num_threads, std::shared_ptr<RGBTRIPLE**> pixels_ptr, std::shared_ptr<std::mutex> pixels_mutex_ptr){
			//initialize shared_ptrs
			worker_mtx_ptr = (std::shared_ptr<std::mutex>)(&worker_mutex);
			request_mtx_ptr = (std::shared_ptr<std::mutex>)(&request_mutex);

			//create a num_threads number of workers
			for(int i = 0; i < num_threads; ++i){
				//create new worker
				Worker worker(pixels_mutex_ptr);
				Worker * new_worker = new Worker(pixels_mutex_ptr);
				//add worker to workers queue
				workers.push(new_worker);
				//now create new thread that runs worker's Run() function, and and add thread to vector
				std::thread * thread = new std::thread(&Worker::Run, new_worker);
				threads.push_back(thread);
			}
		}
		~Dispatcher(){
			while (!workers.empty()){
				delete workers.front();
				workers.pop();
			}
		}

		static void addRequest(Request * request);

		static bool addWorker(Worker * worker, Request * &workers_req_addr);

		static void stop_threads();
};



#endif /* DISPATCHER_H_ */
