#include <stdio.h>
#include <string>

#include "ProcessesTasks.h"

using namespace std;

/* Image reading instructions:
*  https://www.youtube.com/watch?v=utdnjYzlGvY&ab_channel=TripleDistillation
*/


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Syntax: bmpreader <bmp file>\n");
		return 0;
	}

	// Find pixels
	int G = 501;
	int ID = 17;
	int X = G * 2 + ID;
	int A = X % 4;
	int B = 5 + X % 5;

	printf("\nVARIANT\n");
	printf("X = %d; A = %d (cycle type); B = %d (number of threads/processes)\n\n\n", X, A, B);

	Task_CreateProcess(B, argv[1]);

	return 0;
}