#include <iostream>
#include <string>

#include "ProcessesTasks.h"
#include "bmp_reader.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;

/* Image reading instructions:
*  https://www.youtube.com/watch?v=utdnjYzlGvY&ab_channel=TripleDistillation
*/


int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Syntax: bmpreader <bmp file>\n";
		return 0;
	}

	// Read bmp-file
	char* name = (char*)argv[1];
	BMPFile* bmpf = loadBMPFile(name);
	printBMPHeaders(bmpf);
	//printBMPPixels(bmpf);

	// Find pixels
	int G = 501;
	int ID = 17;
	int X = G * 2 + ID;
	int A = X % 4;
	int B = 5 + X % 5;

	cout << "\n\n\nVARIANT\n";
	cout << "X = " << X << "; A = " << A << " (cycle type); B = " << B << " (number of threads/processes)\n\n\n";

	Task_fork(B, bmpf);

	freeBMPFile(bmpf);
	return 0;
}