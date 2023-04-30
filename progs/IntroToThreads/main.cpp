#include <iostream>
#include "./include/Lessons.h"


/*******	 Multithreading		*******/

/*
*	namespace this_thread
*/


// When the process starts, one thread is created - the main thread
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	
	les1::task();
	les2::task();
	les3::task();
	les4::task();
	les5::task();
	les6::task();
	les7::task();
	les8::task();
	les9::task();
	
	return 0;
}