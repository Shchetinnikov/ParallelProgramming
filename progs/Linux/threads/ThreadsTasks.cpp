#include <iostream>

#include <pthread.h>  // pthread
#include <vector>

#include "bmp_reader.h"
#include "ThreadsTasks.h"

using namespace std;

pthread_mutex_t* mtx;

void print(int task_num, int ans) {
	pthread_mutex_lock(mtx);
	cout << "\tThread-" << task_num + 1 << ". Number of pixels : " << ans << endl;
	pthread_mutex_unlock(mtx);
}

void* func(void* arg) {
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
void Task_brute(const BMPFile* bmpf) {
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

// Pthread
void Task_pthread(int B, const BMPFile* bmpf) {
	printf("\"Task_pthread\" is started ..\n");

	vector<pthread_t> ths(B);
	vector<TASK> tasks(B);
	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
	int counter = 0;

	for (int i = 0; i < B; i++) {
		tasks[i].task_num = i;
		tasks[i].B = B;
		tasks[i].img_size = img_size;
		tasks[i].data = bmpf->data;
		tasks[i].ans = 0;
		tasks[i].print = print;
	
		pthread_create(&ths[i] , NULL, func, &tasks[i]);
	}

	for (int i = 0; i < B; i++)
		pthread_join(ths[i], NULL);

	for (int i = 0; i < B; i++) {
		counter += tasks[i].ans;
	}
	cout << "\tTotal number of pixels: " << counter << endl << endl;
}
