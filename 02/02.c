
#include <stdio.h>
#include <mpi.h>
void  main(int argc, char *argv[]){
    int rank_actual;
    int count = 1;
    int buffer = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    {
        MPI_Comm_rank( MPI_COMM_WORLD , &rank_actual);
        MPI_Send(&buffer, count, MPI_INT,rank_actual, 10, MPI_COMM_WORLD);
        MPI_Recv(&buffer, count, MPI_INT, MPI_ANY_SOURCE , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("rank %d tag %d\n", rank_actual, status.MPI_TAG);
    }
    MPI_Finalize();
}