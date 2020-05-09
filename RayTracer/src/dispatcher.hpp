/*
 * dispatcher.hpp
 *
 *  Created on: May 9, 2020
 *      Author: Jpost
 */

#ifndef DISPATCHER_HPP_
#define DISPATCHER_HPP_

#include "dispatcher.h"

std::mutex Dispatcher::worker_mutex;
std::mutex Dispatcher::request_mutex;

std::queue<Worker *> workers;
std::queue<Request *> requests;
std::vector<std::thread *> threads{};

//initialize shared_ptrs
std::shared_ptr<std::mutex> Dispatcher::worker_mtx_ptr ((std::shared_ptr<std::mutex>)(&Dispatcher::worker_mutex));
std::shared_ptr<std::mutex> Dispatcher::request_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::request_mutex));

void Dispatcher::init(int num_threads, std::shared_ptr<RGBTRIPLE**> pixels_ptr, std::shared_ptr<std::mutex> pixels_mutex_ptr){

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

void Dispatcher::addRequest(Request * request){
	worker_mutex.lock();
	if (!workers.empty()){
		//if worker is in queue, we know it's waiting to be called by dispatcher
		workers.front()->addRequest(request);
		workers.front()->notifyOfRequest();
		(*(workers.front()->getMyCondVar())).notify_one();
		workers.pop();
		worker_mutex.unlock();
	} else {
		worker_mutex.unlock();
		request_mutex.lock();
		requests.push(request);
		request_mutex.unlock();
	}
}

bool Dispatcher::addWorker(Worker * worker, Request * &workers_req_addr){
	// returns true if the worker is added to worker_queue
	request_mutex.lock();
	if (!requests.empty()){
		workers_req_addr = requests.front();
		requests.pop();
		request_mutex.unlock();
	} else {
		request_mutex.unlock();
		worker_mutex.lock();
		workers.push(worker);
		worker_mutex.unlock();
		return true;
	}
	return false;
}

void Dispatcher::stop_threads(){
	while(1){
		if(request_mutex.try_lock()){
			if (requests.empty()){
				//then we're done. join and destroy all worker threads
				for(auto it = threads.begin(); it != threads.end(); ++it){
					(*(*it)).join();
				}
				break;
			}
		}
	}
}



#endif /* DISPATCHER_HPP_ */
