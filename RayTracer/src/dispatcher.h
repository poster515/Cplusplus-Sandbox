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

class Worker;

class Dispatcher {
	private:


	public:
		static std::queue<Worker *> workers;
		static std::queue<Request *> requests;
		static std::vector<std::thread *> threads;

		static std::mutex worker_mutex;
		static std::shared_ptr<std::mutex> worker_mtx_ptr;
		static std::mutex request_mutex;
		static std::shared_ptr<std::mutex> request_mtx_ptr;

		static std::condition_variable cv;

		Dispatcher(){}
		~Dispatcher();

		static void init(int num_threads, std::shared_ptr<RGBTRIPLE**> pixels_ptr, std::shared_ptr<std::mutex> pixels_mutex_ptr);
		static void addRequest(Request * request);
		static bool addWorker(Worker * worker, Request * &workers_req_addr);
		static void stop_threads();
};



#endif /* DISPATCHER_H_ */
