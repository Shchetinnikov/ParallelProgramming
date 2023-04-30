#pragma once
#include <Windows.h>

#include "bmp_reader.h"

typedef struct TASK {
	int task_num;
	int B;
	int img_size;
	unsigned char* data;
	int ans;
	void (__stdcall *print)(int, int);
} TASK;


void __stdcall print_1(int task_num, int ans);
void __stdcall print_2(int task_num, int ans);
DWORD __stdcall func(void* arg);

void __stdcall Task_brute(const BMPFile* bmpf);
void __stdcall Task_CreateThread(int B, const BMPFile* bmpf);
void __stdcall Task_std_thread(int B, const BMPFile* bmpf);
void __stdcall Task_omp(int B, const BMPFile* bmpf);