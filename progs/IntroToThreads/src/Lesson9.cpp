#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

#include "../include/Lesson9.h"
#include "../include/Timer.h"

/*******	 Multithreading		*******/

/*******    	Lesson 9		*******/
/*
*	unique_lock
*	protection of shared data
*	synchronization of threads
*/


/*
unique_lock can work differently when we create an object of this class,
it can immediately call the lock method of our mutex, so it may not do
this at the moment of leaving the scope, releases mutex,
unique_lock is more flexible compared to lock_guard
*/

std::mutex mtx3;

void les9::print(char ch) {
	// We specify unique_lock that lock will be called manually (we distinguish)
	std::unique_lock<std::mutex> ul(mtx3, std::defer_lock);

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// Call lock on mutex when creating a unique_lock
	// unique_lock<mutex> ul(mtx3);

	ul.lock();

	for (int i = 0; i < 5; ++i) {
		for (int i = 0; i < 10; i++) {
			std::cout << ch;
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	ul.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void les9::task() {
	MyTimer::Timer timer;

	std::thread th1(les9::print, '*');
	std::thread th2(les9::print, '#');

	th1.join();
	th2.join();

	return;
}