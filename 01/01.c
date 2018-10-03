#include <stdio.h>
#include <mpi.h>

int es_par(int);

void  main(int argc, char *argv[]){
    int rank_actual, buffer = 0,count = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    {
        MPI_Comm_rank( MPI_COMM_WORLD , &rank_actual);
        if (es_par(rank_actual)==1){
            printf("soy par // rank_actual = %d\n", rank_actual );           
            MPI_Send(&buffer, count, MPI_INT,rank_actual+1, 0, MPI_COMM_WORLD);
            buffer = rank_actual;
            MPI_Recv(&buffer, count, MPI_INT, rank_actual+1, 0, MPI_COMM_WORLD, &status);
            printf("buffer par :%d --- source %d \n", buffer, status.MPI_SOURCE );
        }else{
            printf("soy impar // rank_actual = %d\n", rank_actual );
            MPI_Recv(&buffer, count, MPI_INT,rank_actual-1, 0, MPI_COMM_WORLD, &status);
            MPI_Send(&buffer, count, MPI_INT,rank_actual-1, 0, MPI_COMM_WORLD);
            buffer = rank_actual;
            printf("buffer impar :%d --- source :%d \n", buffer ,  status.MPI_SOURCE);
        }
    }
    MPI_Finalize();
}

int es_par(int code){
    if(code % 2) 
        return -1;
    else
        return 1;
}
//status.MPI_TAG;
//status.MPI_SOURCE;
//status.MPI_COUNT;