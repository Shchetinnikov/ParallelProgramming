#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ProcessesTasks.h"
#include "bmp_reader.h"

using namespace std;


void print(int task_num, int ans) {
	cout << "\Process-" << task_num + 1 << ". Number of pixels : " << ans << endl;
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


void Task_fork(int B, const BMPFile* bmpf) {
	int counter = 0;
	
	pid_t pid;
	int status;

	TASK* shared_memory = (TASK*)mmap(NULL, sizeof(TASK) * B, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;

	pid = getpid();

	for (int i = 0; i < B; i++) {
		if (fork()) {
			shared_memory[i].task_num = i;
			shared_memory[i].B = B;
			shared_memory[i].img_size = img_size;
			shared_memory[i].data = bmpf->data;
			shared_memory[i].ans = 0;
			shared_memory[i].print = print;

			func(&shared_memory[i]);

			wait(&status);
			break;
		}
	}

	if (pid == getppid()) {
		for (int i = 0; i < B; i++) {
			counter += shared_memory[i].ans;
		}
		cout << "\tTotal number of pixels: " << counter << endl << endl;
	}
}
