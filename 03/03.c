#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define RANK_ZERO 0
#define RANK_PAR 1
#define RANK_IMPAR 2 

void  main(int argc, char *argv[])
{
    int rank_actual, size_comm, count = 1, buffer = 0, N = 0;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size( MPI_COMM_WORLD , &size_comm);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank_actual);    
    {
        //RANK 0
        if(rank_actual==RANK_ZERO){
            ///////////MPI_Send(buffer, count, datatype, dest, tag, comm)
            for(int i=1; i<size_comm+1;i++){
                if(i%2){ //si es impar
                    MPI_Send(&buffer, count, MPI_INT, RANK_IMPAR , i, MPI_COMM_WORLD);
                }else{   //si es par
                    MPI_Send(&buffer, count, MPI_INT, RANK_PAR , i, MPI_COMM_WORLD);
                } 
            }
            
        }
        ////MPI_Recv(buffer, count, datatype, source, tag, comm, status)
        if(rank_actual == RANK_PAR){
            int size_actual=(size_comm/2);
            while(size_actual>0){
                MPI_Recv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("rank_actual %d : tag %d\n", rank_actual, status.MPI_TAG);
                size_actual--;
            }
        }
        if(rank_actual == RANK_IMPAR){
            int size_actual=(size_comm/2);
            while(size_actual>0){
                MPI_Recv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("rank_actual %d : tag %d\n", rank_actual, status.MPI_TAG);
                size_actual--;
            }  
        }
    }
    MPI_Finalize();
}

//Escriba un programa dónde: • rank 0: genera una N mensajes 
//de contenido aleatorio • rank 1: Recibe los mensajes 
//con tag par • rank 2: Recibe los mensajes con tag 
//inpar Los procesos con rank 1 y 2 saben el N.