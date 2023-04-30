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
    int group_rank;
    MPI_Group group;
   
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);  
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    int G = 501;
    int ID = 17;
    int X = G * 2 + ID;
    int A = X % 4;
    int B = 5 + X % 5;

    if (world_rank == 0) {
        MPI_Group new_group1;
        MPI_Group new_group2;

        printf("\nVARIANT\n");
        printf("X = %d; A = %d (cycle type); B = %d (number of threads / processes);\n\n\n", X, A, B);
        
        int* ranks_1 = (int*)malloc(sizeof(int) * (B - (B % 2)));
        for (int i = 0; i < B - (B % 2); i++) {
            ranks_1[i] = i;
        }
        int* ranks_2 = (int*)malloc(sizeof(int) * (B % 2));
        for (int i = 0; i < B % 2; i++) {
            ranks_2[i] = i + B - (B % 2);
        }

        MPI_Comm_group(MPI_COMM_WORLD, &group);

        MPI_Group_incl(group, B - (B % 2), ranks_1, &new_group1);
        MPI_Group_incl(group, B % 2, ranks_2, &new_group2);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    
    MPI_Comm_group(MPI_COMM_WORLD, &group);
    MPI_Group_rank(group, &group_rank);

   
    int ans = func(world_rank, B, argv[1]);
    int counter = 0;

    printf("Wolrd_Rank: %d,  Group_Rank: %d, Pixels: %d\n", world_rank, group_rank, ans);
    
    MPI_Reduce(&ans, &counter, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        printf("Total number of pixeles: %d\n", counter);
    }

    MPI_Finalize();
}