#include <mpi.h>
#include <iostream>
#include <chrono>
#include "windows.h"

#include "bmp_reader.h"

using namespace std;

/* Image reading instructions:
*  https://www.youtube.com/watch?v=utdnjYzlGvY&ab_channel=TripleDistillation
*/


int __stdcall func(int world_rank, int proc_count, char* name) {
    //Read bmp-file
    BMPFile* bmpf = loadBMPFile(name);

    int task_num = world_rank - 1;
    int img_size = bmpf->dhdr.width * bmpf->dhdr.height;
    int index = (img_size * 3 - 3) - task_num * 3;
    int ans = 0;

    for (index; index >= 0; index -= proc_count * 3) {
        if (bmpf->data[index] * bmpf->data[index + 1] * bmpf->data[index + 2] < 1000)
            ans++;
    }

    return ans;
}



int main(int argc, char** argv) {
    int world_size;
    int world_rank;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int G = 501;
    int ID = 17;
    int X = G * 2 + ID;
    int A = X % 4;
    int B = 5 + X % 5;

    int ans = func(world_rank, B, argv[1]);
    int counter = 0;

    printf("Rank: %d,  Pixels: %d\n", world_rank, ans);
    
    MPI_Reduce(&ans, &counter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("\nVARIANT\n");
        printf("X = %d; A = %d (cycle type); B = %d (number of threads / processes);\n\n\n", X, A, B);

        printf("Total number of pixeles: %d\n", counter);
    }

    MPI_Finalize();
}