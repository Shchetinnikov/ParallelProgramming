#pragma once

#include "bmp_reader.h"


typedef struct TASK {
	int task_num;
	int B;
	int img_size;
	unsigned char* data;
	int ans;
	void (*print)(int, int);
} TASK;


void print(int task_num, int ans);
void* func(void* arg);

void Task_fork(int B, const BMPFile* bmpf);
