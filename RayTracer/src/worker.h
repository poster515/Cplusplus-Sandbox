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
#include <atomic>
#include <condition_variable>

class Request;

class Worker {
	private:
		Request *my_req;
		std::atomic<bool> running;
		std::atomic<bool> stopped;
		std::atomic<bool> has_request;
		std::condition_variable cv;
		std::mutex my_mutex;
		std::unique_lock<std::mutex> ulock;
		std::shared_ptr<std::mutex> addworker_mtx_ptr;

	public:
		Worker(std::shared_ptr<std::mutex> aw_mtx_ptr){
			running = false;
			stopped = false;
			has_request = false;
			my_req = nullptr;
			ulock = std::unique_lock<std::mutex>(my_mutex);
			addworker_mtx_ptr = aw_mtx_ptr;
		}
		~Worker(){
			if (this->my_req != nullptr){
				delete my_req;
			}
		}
		void Run();

		void Stop(){ stopped = true; running = false; }
		void addRequest(Request *req){ my_req = req; }
		void notifyOfRequest(){ has_request = true; }
		std::condition_variable * getMyCondVar(){ return &cv; }
		bool checkRequest(){ return has_request; }
};


#endif /* WORKER_H_ */
