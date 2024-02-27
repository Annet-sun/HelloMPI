#include <stdio.h> 
#include "mpi.h"
#include <iostream>

using namespace std;
int main3(int argc, char** argv) {
    int rank;
    int a[10];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(0));

    if (rank == 0) {
        for (int i = 0; i < size(a); ++i) a[i] = rand();
        MPI_Send(a, size(a), MPI_INT, 1, 100, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(a, size(a), MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        for (int i = 0; i < size(a); i++)
            printf("%d ", a[i]);
    }
    MPI_Finalize();
}
//C:\MPI\HelloMPI\x64\Debug\HelloMPI.exe
