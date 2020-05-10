/*
 * dispatcher.hpp
 *
 *  Created on: May 9, 2020
 *      Author: Jpost
 */

#ifndef DISPATCHER_HPP_
#define DISPATCHER_HPP_

#include "dispatcher.h"
#include "worker.hpp"

std::mutex Dispatcher::worker_mutex;
std::mutex Dispatcher::request_mutex;

std::queue<Worker *> Dispatcher::workers;
std::queue<Request *> Dispatcher::requests;
std::vector<std::thread *> Dispatcher::threads{};

//initialize shared_ptrs
std::shared_ptr<std::mutex> Dispatcher::worker_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::worker_mutex));
std::shared_ptr<std::mutex> Dispatcher::request_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::request_mutex));

void Dispatcher::init(int num_threads, std::shared_ptr<RGBTRIPLE**> pixels_ptr, std::shared_ptr<std::mutex> pixels_mutex_ptr){

	//create a num_threads number of workers
	for(int i = 0; i < num_threads; ++i){
		//create new worker
		Worker * new_worker = new Worker(pixels_mutex_ptr);
		//add worker to workers queue
		Dispatcher::workers.push(new_worker);
		//now create new thread that runs worker's Run() function, and and add thread to vector
		std::thread * thread = new std::thread(&Worker::Run, new_worker);
		Dispatcher::threads.push_back(thread);
	}
}

void Dispatcher::addRequest(Request * request){
	Dispatcher::worker_mutex.lock();
	if (!Dispatcher::workers.empty()){
		//if worker is in queue, we know it's waiting to be called by dispatcher
		Dispatcher::workers.front()->addRequest(request);
		Dispatcher::workers.front()->notifyOfRequest();
		(*(Dispatcher::workers.front()->getMyCondVar())).notify_one();
		Dispatcher::workers.pop();
		Dispatcher::worker_mutex.unlock();
	} else {
		Dispatcher::worker_mutex.unlock();
		Dispatcher::request_mutex.lock();
		Dispatcher::requests.push(request);
		Dispatcher::request_mutex.unlock();
	}
}

bool Dispatcher::addWorker(Worker * worker, Request * &workers_req_addr){
	// returns true if the worker is added to worker_queue
	Dispatcher::request_mutex.lock();
	if (!Dispatcher::requests.empty()){
		workers_req_addr = Dispatcher::requests.front();
		Dispatcher::requests.pop();
		Dispatcher::request_mutex.unlock();
	} else {
		Dispatcher::request_mutex.unlock();
		Dispatcher::worker_mutex.lock();
		Dispatcher::workers.push(worker);
		Dispatcher::worker_mutex.unlock();
		return true;
	}
	return false;
}

void Dispatcher::stop_threads(){
	while(1){
		if(Dispatcher::request_mutex.try_lock()){
			if (Dispatcher::requests.empty()){
				//STOP all workers
				for(auto it = workers.front(); !workers.empty(); ++it){
					//since worker will be waiting, set it to STOP and
					(*it).Stop();
					(*it).addRequest(nullptr);
					(*(*it).getMyCondVar()).notify_one();
				}
				//then we're done. join and destroy all worker threads
				for(auto it = Dispatcher::threads.begin(); it != Dispatcher::threads.end(); ++it){
					(*(*it)).join();
				}
				//finally delete all workers
				while (!Dispatcher::workers.empty()){
					delete Dispatcher::workers.front();
					Dispatcher::workers.pop();
				}
				return;
			}
		}
	}
}

Dispatcher::~Dispatcher(){

}



#endif /* DISPATCHER_HPP_ */
