#include <iostream>
#include <thread>		// working with threads
#include <chrono>

#include "../include/Lesson1.h"


/*******	 Multithreading		*******/
	
/*******    	Lesson 1		*******/
/*
*	threads
*/



// Derived thread
void les1::doWork() {
	for (size_t i = 0; i < 5; i++) {
		std::cout << "Thread ID = " << std::this_thread::get_id();
		std::cout << "\tdoWork " << i <<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void les1::task() {
	std::cout << "Lesson1 is started ..." << std::endl;

	// Creating a thread sample
	std::thread th(les1::doWork);
	std::thread th2(les1::doWork);

	// Definition of the work of the main stream in relation to the derivative
	//th.detach();		// terminates the program without waiting for 'the th' thread to finish
	//th.join();		// terminates the program while waiting for 'the th' thread to finish


	for (size_t i = 0; i < 5; i++) {
		std::cout << "Thread ID = " << std::this_thread::get_id() << "\tmain " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	th.join();
	th2.join();


	/*
	cout << "Start main" << endl;

	// Suspending the current thread for a certain period of time
	this_thread::sleep_for(chrono::milliseconds(3000));

	// Getting the ID of the current thread
	cout << this_thread::get_id() << endl;

	cout << "End main" << endl;
	*/
	
	return;
}