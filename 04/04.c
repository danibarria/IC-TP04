
#include <stdio.h>
#include <mpi.h>

#define RANK_ROOT 0

static long num_steps = 1000000;

MPI_Status status;
int rank_actual, size_comm, for_step, rank_last, rank_first;

double step, pi,x, sum=0.0;

void main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size_comm);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_actual);
    step = 1.0 / (double)num_steps;
    for_step = num_steps / size_comm;
    rank_last = for_step * (rank_actual+1);
    rank_first = for_step * rank_actual;
    for(rank_first; rank_first<rank_last; rank_first++){
        x = (rank_first +0.5) * step ;
        sum = sum  + 4/(1.0+x*x);
    }
    MPI_Reduce(&sum, &pi, 1 , MPI_DOUBLE, MPI_SUM, RANK_ROOT, MPI_COMM_WORLD);
    if(rank_actual == RANK_ROOT){
        pi = pi*step;
        printf("%f\n", pi );
    }
    MPI_Finalize();
}


/*
############### CODIGO VERSION OPENMP

#include <stdio.h> #include <omp.h>
static long num_steps = 100000;
double step;
void main (){ 
    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    #pragma omp parallel
    {
        #pragma omp for private(x,i) reduction(+:sum)
        for (i=0;i< num_steps; i++){
            #pragma omp critical
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }       
    }
    pi = step * sum;
    printf("%e \n",pi);
}*/