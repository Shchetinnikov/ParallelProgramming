#pragma once

#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "bmp_reader.h"

__global__ void kernel(unsigned char* data, int img_size, int B);
void CudaTask(int B, const BMPFile* bmpf);