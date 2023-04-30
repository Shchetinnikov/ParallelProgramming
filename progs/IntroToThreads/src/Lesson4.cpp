#include <iostream>
#include <thread>
#include <chrono>

#include "../include/Lesson4.h"

/*******	 Multithreading		*******/

/*******    	Lesson 4		*******/
/*
*   Getting the results of the function from the thread
*   Lambda expressions
*/


// Derived thread
int les4::doWork(int a, int b) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STARTED" << "\t==========" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STOPPED" << "\t==========" << std::endl;

    return a + b;
}

void les4::task() {
	std::cout << "Lesson4 is started ..." << std::endl;

	int result;

	// Wrapping the lambda expression in a separate thread
	std::thread th([&result]() { result = doWork(2, 5); });

	for (size_t i = 1; i <= 5; i++) {
        std::cout << "Thread ID = " << std::this_thread::get_id();
        std::cout << "\tmain " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	th.join();
	std::cout << "doWork result = " << result << std::endl;

	return;
}
