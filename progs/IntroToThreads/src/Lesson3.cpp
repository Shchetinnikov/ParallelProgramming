#include <iostream>
#include <thread>
#include <chrono>

#include "../include/Lesson3.h"


/*******	 Multithreading		*******/

/*******    	Lesson 3		*******/
/*
*   Getting the results of the function from the thread
*   Passing parameters to the thread by reference/pointer
*/


// Derived thread
void les3::doWork(int &a) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STARTED" << "\t==========" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	 	
	a *= 2;

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STOPPED" << "\t==========" << std::endl;
}

void les3::task() {
	std::cout << "Lesson3 is started ..." << std::endl;

	int q = 5;

	/*Despite the fact that the DoWork3 function accepts a parameter by reference, 
	in the new stream, the q parameter is passed to the DoWork3 function by value.
	To do this, the std::ref(q) construction is used.
	The reference_wrapper function creates a class for the q object*/

	std::thread th(les3::doWork, std::ref(q));

	for (size_t i = 0; i < 5; i++) {
        std::cout << "Thread ID = " << std::this_thread::get_id();
        std::cout << "\tmain works\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	th.join();
	std::cout << q << std::endl;

	return;
}