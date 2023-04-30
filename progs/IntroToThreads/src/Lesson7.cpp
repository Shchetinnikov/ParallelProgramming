#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "../include/Lesson7.h"
#include "../include/Timer.h"

/*******	 Multithreading		*******/

/*******    	Lesson 7		*******/
/*
*   Mutual Blocking or Deadlock
*	protection of shared data
*	synchronization of threads
*/


// Example

std::mutex mtx1;
std::mutex mtx2;


void les7::print1() {
	mtx2.lock();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	mtx1.lock();

	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < 10; i++) {
			std::cout << '*';
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	mtx1.unlock();
	mtx2.unlock();
}

void les7::print2() {
	mtx1.lock();

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	mtx2.lock();

	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < 10; i++) {
			std::cout << '#';
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	mtx1.unlock();
	mtx2.unlock();
}

void les7::task() {
	MyTimer::Timer timer;

	std::thread th1(les7::print1);
	std::thread th2(les7::print2);

	th1.join();
	th2.join();

	return;
}