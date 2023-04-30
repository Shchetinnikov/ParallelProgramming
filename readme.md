# Parallel Programming
Course of parallel programming. National Research Nuclear University MEPhI (Moscow Engineering Physics Institute)

#### List of directories
1. data | Samples of images
2. progs:
    - IntroToThreads | Quick start to threads;
    - WinAPI | Threads and processes in windows;
    - Linux | Threads and processes in linux;
    - MPI | Processes with MPI in linux;
    - CUDA | Processes using GPU in linux.


#### Laboratory works
##### Target
 Find the number of pixels in the image such that the product of its channels is less than 1000: 

##### Tasks:
0. Brute
1. Threads:
    - CreateThread;
    - pthread_create;
    - std::thread;
    - OMP.
2. Processes:
    - CreateProcess;
    - fork.
3. MPI:
    - MPI_p2p;
    - MPI_collective.
4. CUDA
