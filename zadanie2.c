#include <stdio.h>
#include <math.h>
#include "mpi.h"


double funkcja(double x){
    return pow(x, 2);
}

double mProstokaty(double a, int numer_proc, double h){
    double result = 0;
    result = funkcja(a+numer_proc*h);
    return result;
}


double mTrapezy(double a, int numer_proc, double h, int size_n){
    double result = 0;
    if(numer_proc == 0 || numer_proc == size_n) {
        result = funkcja(a+numer_proc*h)/2;
    } else {
        result = funkcja(a+numer_proc*h);
    }
    return result;
}


int main( int argc, char **argv )
{
    int numer_proc;
    double result = 0;
    double pole = 0;
    int size_n;
    int tag = 400;
    
    double xp = 1;
    double xk = 4;
    
    MPI_Status status;

    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &size_n);
    MPI_Comm_rank( MPI_COMM_WORLD, &numer_proc);

    double dx = (xk - xp)/size_n;

    if(numer_proc == size_n-1){
        pole = mTrapezy(xp, numer_proc+1, dx, size_n);
        //pole = mProstokaty(xp, numer_proc+1, dx);
        result += dx*pole;

        printf("Metoda Trapezow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        //printf("Metoda Prostokatow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        MPI_Send(&result, 1, MPI_DOUBLE, numer_proc-1, tag, MPI_COMM_WORLD);
    }

    if(numer_proc != size_n-1){
        MPI_Recv(&result, 1, MPI_DOUBLE, numer_proc+1, tag, MPI_COMM_WORLD, &status);
        pole = mTrapezy(xp, numer_proc+1, dx, size_n);
        //pole = mProstokaty(xp, numer_proc+1, dx);
        result += dx*pole;
       
        printf("Metoda Trapezow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        //printf("Metoda Prostokatow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        if(numer_proc != 0){
            MPI_Send(&result, 1, MPI_DOUBLE, numer_proc-1, tag, MPI_COMM_WORLD);
        }
    } 
    MPI_Finalize();
    return 0;
}
