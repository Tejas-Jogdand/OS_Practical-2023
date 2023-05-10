#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define N 1000

int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int i;
    int local_sum = 0;
    int global_sum;
    double local_average, global_average;
    int *arr = (int *)malloc(N * sizeof(int));


    srand(rank);

    for (i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
        local_sum += arr[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    local_average = (double)local_sum / N;
    MPI_Reduce(&local_average, &global_average, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    global_average /= size;

    if (rank == 0)
    {
        printf("Global sum=%d\n", global_sum);
        printf("Global average=%.2f\n", global_average);
    }
    MPI_Finalize();
}