#include <iostream>
#include "../include/Timer.h"

MyTimer::Timer::Timer() {
	start = std::chrono::high_resolution_clock::now();
}

MyTimer::Timer::~Timer() {
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	float result = duration.count();
	std::cout << "Time is passed: " << result << " seconds" << std::endl;
}