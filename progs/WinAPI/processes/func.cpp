#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "bmp_reader.h"

using namespace std;


typedef struct TASK {
	int task_num;
	int B;
	int img_size;
	unsigned char* data;
	int ans;
} TASK;


int main(int argc, char* argv[]) {
	char file_name[50];
	sprintf(file_name, ".\\log_%d.txt", atoi(argv[3]));
	
	FILE* fp = fopen(file_name, "wb");
	if (!fp) {
		printf("Can't load file %s", file_name);
		exit(0);
	}

	//Read bmp-file
	char* name = argv[1];
	BMPFile* bmpf = loadBMPFile(name);
	//printBMPHeaders(bmpf);
	//printBMPPixels(bmpf);

	int img_size = bmpf->dhdr.width * bmpf->dhdr.height;

	TASK task;
	task.task_num = atoi(argv[3]);
	task.B = atoi(argv[2]);
	task.img_size = img_size;
	task.data = bmpf->data;
	task.ans = 0;

	int index = (task.img_size * 3 - 3) - task.task_num * 3;
	for (index; index >= 0; index -= task.B * 3) {
		if (task.data[index] * task.data[index + 1] * task.data[index + 2] < 1000)
			task.ans++;
	}

	printf("\Process-%d. Number of pixels: %d\n", task.task_num + 1, task.ans);
	fwrite(&task.ans, sizeof(int), 1, fp);

	fclose(fp);
	freeBMPFile(bmpf);
	return 0;
}