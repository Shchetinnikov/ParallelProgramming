#include <iostream>
#include <thread>
#include <mutex>

#include "../include/Lesson6.h"
#include "../include/Timer.h"


/*******	 Multithreading		*******/

/*******    	Lesson 6		*******/
/*
*   mutex, lock_guard
*	protection of shared data
*	synchronization of threads
*/


/*
(see Wikipedia for more information)
Mutex(English mutex, from mutual exclusion � "mutual exclusion")� 
this is the basic synchronization mechanism.It is designed to organize mutually 
exclusive access to shared data for multiple threads using memory barriers
(for simplicity, we can consider a mutex as a door leading to shared data)
*/

/*
lock_guard is a class whose task is to capture mutex in the constructor 
when creating an object of such a classand release this mutex in the destructor 
at the moment when an object of this class leaves any scope.

lock_guard : when an object is created, it tries to get the mutex(by calling lock()), 
and when the object is destroyed, it automatically releases the mutex(by calling unlock())
*/


std::mutex mtx;

// void les6::print(char ch){
// 	std::this_thread::sleep_for(std::chrono::milliseconds(20));

// 	mtx.lock();

// 	for (int i = 0; i < 5; ++i) {
// 		for (int i = 0; i < 10; i++) {
// 			std::cout << ch;
// 			std::this_thread::sleep_for(std::chrono::milliseconds(20));
// 		}
// 		std::cout << std::endl;
// 	}
// 	std::cout << std::endl;

// 	mtx.unlock();

// 	std::this_thread::sleep_for(std::chrono::milliseconds(20));
// }


void les6::print(char ch) {
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	
	{
		// Limited the scope for lock_guard
		std::lock_guard<std::mutex> guard(mtx);

		for (int i = 0; i < 5; ++i) {
			for (int i = 0; i < 10; i++) {
				std::cout << ch;
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void les6::task()
{
	MyTimer::Timer timer;

	std::thread th1(les6::print, '*');
	std::thread th2(les6::print, '#');

	th1.join();
	th2.join();

	return;
}