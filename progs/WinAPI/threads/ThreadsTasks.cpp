#include <iostream>

#include <Windows.h>	// CreatThread
#include <thread>		// std::thread
#include <omp.h>		// OpenMP

#include <mutex>		
#include <vector>

#include "bmp_reader.h"
#include "ThreadsTasks.h"

using namespace std;

CRITICAL_SECTION cs;
mutex mtx;
omp_lock_t writelock;

void __stdcall print_1(int task_num, int ans) {
	EnterCriticalSection(&cs);
	cout << "\tThread-" << task_num + 1 << ". Number of pixels : " << ans << endl;
	LeaveCriticalSection(&cs);
}

void __stdcall print_2(int task_num, int ans) {
	mtx.lock();
	cout << "\tThread-" << task_num + 1 << ". Number of pixels : " << ans << endl;
	mtx.unlock();
}

void __stdcall print_3(int task_num, int ans) {
	omp_set_lock(&writelock);
	cout << "\tThread-" << task_num + 1 << ". Number of pixels : " << ans << endl;
	omp_unset_lock(&writelock);
}

DWORD __stdcall func(void* arg) {
	TASK* t = (TASK*)arg;
	int index = (t->img_size * 3 - 3) - t->task_num * 3;

	for (index; index >= 0; index -= t->B * 3) {
		if (t->data[index] * t->data[index + 1] * t->data[index + 2] < 1000)
			t->ans++;
	}
	t->print(t->task_num, t->ans);
	return 0;
}


// BRUTE
void __stdcall Task_brute(const BMPFile* bmpf) {
	cout << "\"Task_brute\" is started .." << endl;

	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
	unsigned char* data = bmpf->data;
	int counter = 0;

	for (int i = 0; i < img_size * 3; i += 3) {
		if (data[i] * data[i + 1] * data[i + 2] < 1000)
			counter++;
	}

	cout << "\tTotal number of pixels: " << counter << endl << endl;
}


// CTREATE_THREAD
void __stdcall Task_CreateThread(int B, const BMPFile* bmpf) {
	cout << "\"Task_CreateThread\" is started .." << endl;

	HANDLE* ths = (HANDLE*)malloc(sizeof(HANDLE) * B);
	TASK* tasks = (TASK*)malloc(sizeof(TASK) * B);

	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
	int counter = 0;

	InitializeCriticalSection(&cs);

	for (int i = 0; i < B; i++) {
		tasks[i].task_num = i;
		tasks[i].B = B;
		tasks[i].img_size = img_size;
		tasks[i].data = bmpf->data;
		tasks[i].ans = 0;
		tasks[i].print = print_1;

		ths[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, &tasks[i], 0, NULL);
	}
	WaitForMultipleObjects(B, ths, TRUE, INFINITE);

	DeleteCriticalSection(&cs);

	for (int i = 0; i < B; i++) {
		counter += tasks[i].ans;
		TerminateThread(ths[i], 0);
	}
	free(ths);
	free(tasks);

	cout << "\tTotal number of pixels: " << counter << endl << endl;
}

// STD_THREAD
void __stdcall Task_std_thread(int B, const BMPFile* bmpf) {
	cout << "\"Task_std_thread\" is started .." << endl;
	
	vector<thread> ths(B);
	vector<TASK> tasks(B);
	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
	int counter = 0;

	for (int i = 0; i < B; i++) {
		tasks[i].task_num = i;
		tasks[i].B = B;
		tasks[i].img_size = img_size;
		tasks[i].data = bmpf->data;
		tasks[i].ans = 0;
		tasks[i].print = print_2;

		ths[i] = thread(func, &tasks[i]);
	}

	for (int i = 0; i < B; i++) {
		ths[i].join();
	}

	for (int i = 0; i < B; i++) {
		counter += tasks[i].ans;
	}

	cout << "\tTotal number of pixels: " << counter << endl << endl;
}


// OpenMP
void __stdcall Task_omp(int B, const BMPFile* bmpf) {
	printf("\"Task_omp\" is started ..\n");

	vector<TASK> tasks(B);
	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
	int counter = 0;
	
	omp_set_nested(1);
	omp_init_lock(&writelock);

	#pragma omp parallel num_threads(B)
	#pragma omp single	
	for (int i = 0; i < B; i++) {
		
		#pragma omp task
		tasks[i].task_num = i;
		tasks[i].B = B;
		tasks[i].img_size = img_size;
		tasks[i].data = bmpf->data;
		tasks[i].ans = 0;
		tasks[i].print = print_3;
	
		func(&tasks[i]);
	}
	omp_destroy_lock(&writelock);

	for (int i = 0; i < B; i++) {
		counter += tasks[i].ans;
	}
	cout << "\tTotal number of pixels: " << counter << endl << endl;
}