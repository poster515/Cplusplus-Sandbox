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

//forward declare this structure
struct RGBTRIPLE;

class Worker {
	public:
		//need to constantly be scanning Dispatcher's "requests" queue and grab one if available
};

class Request {
	//should be generic.
	//give an x and y coordinate, and memory location of "pixels"
};

class Dispatcher {
	private:
		std::queue<int> worker_threads;
		std::queue<int> requests;

		std::mutex worker_mutex;
		std::mutex request_mutex;

	public:
		Dispatcher(int num_threads){
			for(int i = 0; i < num_threads; ++i){
				//create a num_threads number of worker_threads, and initialize them in waiting state

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
