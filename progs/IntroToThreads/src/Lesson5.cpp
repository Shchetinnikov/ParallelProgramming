#include <iostream>
#include <thread>
#include <chrono>

#include "../include/Lesson5.h"

/*******	 Multithreading		*******/

/*******    	Lesson 5		*******/
/*
*   Running a class method in a separate thread
*/


void les5::MyClass::doWork() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STARTED" << "\t==========" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork is STOPPED" << "\t==========" << std::endl;

    return;
}

void les5::MyClass::doWork2(int a) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork2 is STARTED" << "\t==========" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::cout << "doWork2 parameter value\t" << a << std::endl;
    std::cout << "Theard ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "doWork2 is STOPPED" << "\t==========" << std::endl;

    return;
}

int les5::MyClass::sum(int a, int b) const {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "Sum is  STARTED" << "\t==========" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Thread ID = " << std::this_thread::get_id();
    std::cout << " ==========\t" << "Sum is STOPPED" << "\t==========" << std::endl;

    return a + b;
}

void les5::task() {
#if 0
	int result;
	les5::MyClass m;

	std::thread th([&]() { result = m.sum(2, 5); });

	for (size_t i = 1; i <= 5; i++) {
        std::cout << "Thread ID = " << std::this_thread::get_id();
        std::cout << "\tmain " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	th.join();
	std::cout << "RESULT = " << result << std::endl;

#elif 1
	les5::MyClass m;
	//std::thread th(&les5::MyClass::doWork, m);
	std::thread th(&les5::MyClass::doWork2, m, 5);

	/*std::thread th([&m]() { m.doWork(); });*/

	for (size_t i = 1; i <= 5; i++) {
        std::cout << "Thread ID = " << std::this_thread::get_id();
        std::cout << "\tmain " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

	th.join();

#endif	
	return;
}