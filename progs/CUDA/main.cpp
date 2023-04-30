#include <stdio.h>
#include "bmp_reader.h"
#include "CudaTasks.h"


int main(int argc, char* argv[]){
  if (argc < 2) {
    printf("Syntax: bmpreader <bmp file>\n");
    return 0;
  }

  // Read bmp-file
  char* name = (char*)argv[1];
  BMPFile* bmpf = loadBMPFile(name);
  // printBMPHeaders(bmpf);
  //printBMPPixels(bmpf);

  // Find pixels
  int G = 501;
  int ID = 17;
  int X = G * 2 + ID;
  int A = X % 4;
  int B = 5 + X % 5;

  printf("\nVARIANT\n");
  printf("X = %d; A = %d (cycle type); B = %d (number of threads/processes)\n\n\n", X, A, B);

  CudaTask(B, bmpf);

  freeBMPFile(bmpf);
  return 0;
}