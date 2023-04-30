# Parallel Programming
Course of parallel programming. National Research Nuclear University MEPhI (Moscow Engineering Physics Institute)

#### List of directories
1. data | Samples of images
2. progs:
    2.1. IntroToThreads | Quick start to threads;
    2.2. WinAPI | Threads and processes in windows;
    2.3. Linux | Threads and processes in linux;
    2.4. MPI | Processes with MPI in linux;
    2.5. CUDA | Processes using GPU in linux.


#### Laboratory works
##### Target
 Find the number of pixels in the image such that the product of its channels is less than 1000: 

##### Tasks:
0. Brute
1. Threads:
    1.1. CreateThread;
    1.2. pthread_create;
    1.3. std::thread;
    1.4. OMP.
2. Processes:
    2.1. CreateProcess;
    2.2. fork.
3. MPI:
    3.1. MPI_p2p;
    3.2. MPI_collective.
4. CUDA
