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
    int local_min = 100;
    int local_max = 0;
    int global_min, global_max;
    int *arr = (int *)malloc(N * sizeof(int));

    srand(rank);

    for (i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;
        if (arr[i] < local_min)
        {
            local_min = arr[i];
        }
        if (arr[i] > local_max)
        {
            local_max = arr[i];
        }
    }

    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Global min=%d\n", global_min);
        printf("Global max=%d\n", global_max);
    }
    MPI_Finalize();
}
