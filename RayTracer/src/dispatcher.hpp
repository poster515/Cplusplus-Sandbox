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
std::mutex Dispatcher::addworker_mutex;

std::queue<Worker *> Dispatcher::workers;
std::queue<Request *> Dispatcher::requests;
std::vector<std::pair<std::thread *, Worker *>> Dispatcher::threads;

//initialize shared_ptrs
std::shared_ptr<std::mutex> Dispatcher::worker_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::worker_mutex));
std::shared_ptr<std::mutex> Dispatcher::request_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::request_mutex));
std::shared_ptr<std::mutex> Dispatcher::stdcout_mtx_ptr;
std::shared_ptr<std::mutex> Dispatcher::count_mtx_ptr;
std::shared_ptr<std::mutex> Dispatcher::addworker_mtx_ptr((std::shared_ptr<std::mutex>)(&Dispatcher::addworker_mutex));

unsigned int Dispatcher::num_threads;
int Dispatcher::count;


void Dispatcher::init(int num_threads,
						std::shared_ptr<std::mutex> pixels_mutex_ptr,
						std::shared_ptr<std::mutex> cout_mtx_ptr,
						std::shared_ptr<std::mutex> count_mtx_ptr){

	Dispatcher::num_threads = num_threads;
	Dispatcher::count_mtx_ptr = count_mtx_ptr;
	stdcout_mtx_ptr = cout_mtx_ptr;
	//create a num_threads number of workers
	for(int i = 0; i < num_threads; ++i){
		//create new worker
		Worker * new_worker = new Worker(Dispatcher::addworker_mtx_ptr);
		//now create new thread that runs worker's Run() function, and and add thread to vector
		std::thread * thread = new std::thread(&Worker::Run, new_worker);
		Dispatcher::threads.push_back(std::pair<std::thread *, Worker *>(thread, new_worker));
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
//	delete all workers

	while(!Dispatcher::threads.empty()){
		auto it = Dispatcher::threads.begin();
		(std::get<1>(*it))->addRequest(nullptr);
		(std::get<1>(*it))->notifyOfRequest();
		(std::get<1>(*it))->Stop();
		(std::get<1>(*it))->getMyCondVar()->notify_one();

		(*Dispatcher::stdcout_mtx_ptr).lock();
		std::cout << "deleting worker" << std::endl;
		(*Dispatcher::stdcout_mtx_ptr).unlock();

		if ((std::get<0>(*it))->joinable()){
			(*Dispatcher::stdcout_mtx_ptr).lock();
			std::cout << "joining thread: " << (std::get<0>(*it))->get_id() << std::endl;
			(*Dispatcher::stdcout_mtx_ptr).unlock();

			if ((std::get<0>(*it))->joinable()){
				(std::get<0>(*it))->join();
			}
		}
		(*Dispatcher::stdcout_mtx_ptr).lock();
		std::cout << "thread is joined" << std::endl;
		(*Dispatcher::stdcout_mtx_ptr).unlock();
		//now delete worker completely
		delete (std::get<1>(*it));
		delete (std::get<0>(*it));
		Dispatcher::threads.erase(Dispatcher::threads.begin());
	}
}

Dispatcher::~Dispatcher(){

}



#endif /* DISPATCHER_HPP_ */
