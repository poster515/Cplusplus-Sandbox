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
#include <condition_variable>

class Request;

class Worker {
	private:
		Request *my_req;
		bool running;
		bool stopped;
		bool has_request;
		std::condition_variable cv;
		std::shared_ptr<std::mutex> pixels_mtx_ptr;

	public:
		Worker(std::shared_ptr<std::mutex> p_mtx_ptr){
			running = false;
			stopped = false;
			has_request = false;
			my_req = nullptr;
			pixels_mtx_ptr = p_mtx_ptr;
		}
		~Worker(){

		}
		void Run();

		void Stop(){ running = false; }
		void addRequest(Request *req){ my_req = req; }
		void notifyOfRequest(){ has_request = true; }
		std::condition_variable * getMyCondVar(){ return &cv; }
		bool checkRequest(){ return has_request; }
};


#endif /* WORKER_H_ */
