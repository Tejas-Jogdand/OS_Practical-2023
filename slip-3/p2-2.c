#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define N 1000

int main(int argc, char **argv){
    int rank, size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int i, local_sum,global_sum;
    double global_average,local_average; 
    int *arr=(int*)malloc(N*sizeof(int));

    srand(rank);
    
    for (i=0;i<N;i++)
    {
        arr[i]=rand()%100;
        local_sum+=arr[i];
    }

    MPI_Reduce(&local_sum,$global_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&local_average,&global_average,1,MPI_DOUBLE,MPI_SUM,0,MPI_WOLRD_COMM);

    if(rank==0){
        printf("Global sum: %d",global_sum);
        printf("Global Averaage: %d",global_average);
    }

    MPI_Finalize();
}