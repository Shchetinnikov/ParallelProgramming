#include "CudaTasks.h"

__global__ void kernel(unsigned char* data, int img_size, int B, int* out) {
	int tid = blockIdx.x * blockDim.x + threadIdx.x;

  if (tid < B) {
    int index = (img_size * 3 - 3) - tid * 3;
    int ans = 0;

    for (index; index >= 0; index -= B * 3) {
      if (data[index] * data[index + 1] * data[index + 2] < 1000) {
        ans++;
      }
    }
    out[tid] = ans;
    printf("\tThread-%d. Number of pixels: %d \n", tid + 1, ans);
  }
  __syncthreads();
}


void CudaTask(int B, const BMPFile* bmpf) {
  unsigned char *d_data;
  int *d_out;

  int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
  unsigned char* h_data = bmpf->data;
  int *out = (int*)malloc(sizeof(int) * B);
  
  for(int i = 0; i < B; i++) { out[i] = 0; }

  cudaMalloc((unsigned char**)&d_data, sizeof(unsigned char) * img_size);
  cudaMalloc((int**)&d_out, sizeof(int) * B);

  cudaMemcpy(d_data, h_data, sizeof(unsigned char) * img_size, cudaMemcpyHostToDevice);

  int block_size = 32;
  int grid_size = 1;
  kernel<<<grid_size, block_size>>>(d_data, img_size, B, d_out);

  cudaMemcpy(out, d_out, sizeof(int) * B, cudaMemcpyDeviceToHost);

  int res = 0;
  for(int i = 0; i < B; i++) {
    res += out[i];
  }
  printf("\tTotal number of pixels: %d\n\n", res);

  cudaFree(d_data);
  cudaFree(d_out);
  free(out);
}