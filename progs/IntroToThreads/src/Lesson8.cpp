#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "../include/Lesson8.h"
#include "../include/Timer.h"

/*******	 Multithreading		*******/

/*******    	Lesson 8		*******/
/*
*   recursive_mutex
*	recursive locking
*	protection of shared data
*	synchronization of threads
*/


std::recursive_mutex rm; // you can capture as many times as we need
std::mutex m;			// causes an error when re-capturing


void les8::foo(int a) {
	rm.lock();
	
	std::cout << a << " ";

	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	if (a <= 1) {
		std::cout << std::endl;
		rm.unlock();
		return;
	}
	a--;
	les8::foo(a);

	rm.unlock();
}

void les8::task() {
	std::thread th1(les8::foo, 10);
	std::thread th2(les8::foo, 10);

	th1.join();
	th2.join();

	return;
}