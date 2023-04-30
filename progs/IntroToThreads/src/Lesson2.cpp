#include <iostream>
#include <thread>		// working with threads
#include <chrono>

#include "../include/Lesson2.h"

/*******	 Multithreading		*******/

/*******    	Lesson 2		*******/
/*
*	Passing parameters to the thread
*/


// Derived thread
void les2::doWork(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	std::cout << "==========\t" << "doWork is STARTED" << "\t==========" << std::endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "a + b = " << a + b << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	std::cout << "==========\t" << "doWork is STOPPED" << "\t==========" << std::endl;

}

void les2::task() {
	std::cout << "Lesson2 is started ..." << std::endl;

	std::thread th(les2::doWork, 2, 3);

	for (size_t i = 0; true; i++) {
		std::cout << "Thread ID = " << std::this_thread::get_id();
		std::cout << "\tmain works\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	th.join();

	return;
}
