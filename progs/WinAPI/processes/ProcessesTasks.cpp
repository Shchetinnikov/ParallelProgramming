#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <tchar.h>

#include "ProcessesTasks.h"


using namespace std;


int __stdcall Task_CreateProcess(int B, char* bmpf_name) {
	HANDLE* hpis = (HANDLE*)malloc(sizeof(PROCESS_INFORMATION) * B);
	const char* ApplicationName = ".\\func.exe";

	for (int i = 0; i < B; i++) {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		char buffer[50];
		sprintf(buffer, "%s %s %d %d", ApplicationName, bmpf_name, B, i);

		if (!CreateProcess(ApplicationName, buffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
			printf("Unable to generate process");
			return -1;
		}

		hpis[i] = pi.hProcess;
	}
	WaitForMultipleObjects(B, hpis, TRUE, INFINITE);

	
	FILE* fp;
	char file_name[50];
	int counter = 0;
	int ans = 0;

	for (int i = 0; i < B; i++) {
		sprintf(file_name, ".\\log_%d.txt", i);
		if ((fp = fopen(file_name, "rb")) == NULL) {
			printf("Cannot open file.\n");
			exit(1);
		}

		fread(&ans, sizeof(int), 1, fp);
		counter += ans;

		fclose(fp);
	}

	printf("\tTotal number of pixels: %d\n\n", counter);
	return 0;
}