#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main( int argc, char **argv )
{
int numer_proc;
double result = 0;
int size_n;
int tag = 400;
MPI_Status status;

MPI_Init( &argc, &argv );
MPI_Comm_size( MPI_COMM_WORLD, &size_n);
MPI_Comm_rank( MPI_COMM_WORLD, &numer_proc);

if(numer_proc == 0){
    result += 4*(pow(-1, numer_proc)/(2*(numer_proc+1)-1));
    printf("Przybliznie PI w procesie nr-%d wynosi = %f\n", numer_proc, result);
    MPI_Send(&result, 1, MPI_INT, numer_proc+1, tag, MPI_COMM_WORLD);
}

if(numer_proc != 0){
    MPI_Recv(&result, 1, MPI_INT, numer_proc-1, tag, MPI_COMM_WORLD, &status);
    //printf("Result-> %d", result);
    result += 4*(pow(-1, numer_proc)/(2*(numer_proc+1)-1));
    printf("Przybliznie PI w procesie nr-%d wynosi = %f\n", numer_proc, result);
    if(numer_proc != size_n-1){
        MPI_Send(&result, 1, MPI_INT, numer_proc+1, tag, MPI_COMM_WORLD);
    }
}

MPI_Finalize();
return 0;
}
