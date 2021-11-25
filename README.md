# PRiR-Homework_MPI_4
## Zadanie 1 - approximation of the value of PI in MPI
1. Initializing the MPI environment; creating a network of processors with the size passed by the ```-np``` parameter
2. The number of processors making up the network
3. Unique number of the current process
```c
  ...
  MPI_Init( &argc, &argv ); // 1
  MPI_Comm_size( MPI_COMM_WORLD, &size_n); // 2
  MPI_Comm_rank( MPI_COMM_WORLD, &numer_proc); // 3
  ...
```
4. Calculate the approximation of PI for the process nr-0
5. Send the result to the next process
```c
  ...
  // 4
  if(numer_proc == 0){
      result += 4*(pow(-1, numer_proc)/(2*(numer_proc+1)-1));
      printf("Przybliznie PI w procesie nr-%d wynosi = %f\n", numer_proc, result);
      MPI_Send(&result, 1, MPI_DOUBLE, numer_proc+1, tag, MPI_COMM_WORLD); // 5
  }
  ...
```
6. Calculate the approximation of PI for the rest processes 
7. Take the value from the process nr-0 (from the previous process) 
8. Until we get to the end of the ```size_n```, we send ```result``` to the next process
9. Finish work in MPI 
```c
  ...
  // 6
   if(numer_proc != 0){
        MPI_Recv(&result, 1, MPI_DOUBLE, numer_proc-1, tag, MPI_COMM_WORLD, &status); // 7
        //printf("Result-> %d", result);
        result += 4*(pow(-1, numer_proc)/(2*(numer_proc+1)-1));
        printf("Przybliznie PI w procesie nr-%d wynosi = %f\n", numer_proc, result);
        if(numer_proc != size_n-1){
            MPI_Send(&result, 1, MPI_DOUBLE, numer_proc+1, tag, MPI_COMM_WORLD); // 8
        }
   }
  MPI_Finalize(); // 9
  return 0;
```
### Result
![z1-1-1](https://user-images.githubusercontent.com/72127610/142828394-891e472d-f10f-46c9-8b44-d55ffd3d2c31.png)
## Zadanie 2 - Trapezoidal and Rectangle method in MPI
1. Initializing the MPI environment; creating a network of processors with the size passed by the ```-np``` parameter
2. The number of processors making up the network
3. Unique number of the current process
```c
  ...
  MPI_Init( &argc, &argv ); // 1
  MPI_Comm_size( MPI_COMM_WORLD, &size_n); // 2
  MPI_Comm_rank( MPI_COMM_WORLD, &numer_proc); // 3
  ...
```
4. Define the interval <xp, xk> and ```dx``` the length of the division of this interval
```c
  ...
  double xp = 1;
  double xk = 4;
  ...
  double dx = (xk - xp)/size_n;
```
5. Start counting fields from the last process, np. 7
6. Send the result to the previous process(one less), 7-1=6
```c
  ...
    if(numer_proc == size_n-1){
        pole = mTrapezy(xp, numer_proc+1, dx, size_n);
        //pole = mProstokaty(xp, numer_proc+1, dx);
        result += dx*pole;

        printf("Metoda Trapezow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        //printf("Metoda Prostokatow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        MPI_Send(&result, 1, MPI_DOUBLE, numer_proc-1, tag, MPI_COMM_WORLD); // 6
    }
  ...
```
7. Get the result from the process greater by 1
8. Counting fields and add to ````result```
9. Until we get to the end(in this case, to process zero), we send ```result``` to the previous process
10. Finish work in MPI 
```c
  ...
  // 7
    if(numer_proc != size_n-1){
        MPI_Recv(&result, 1, MPI_DOUBLE, numer_proc+1, tag, MPI_COMM_WORLD, &status);
        pole = mTrapezy(xp, numer_proc+1, dx, size_n); // 8
        //pole = mProstokaty(xp, numer_proc+1, dx);
        result += dx*pole;

        printf("Metoda Trapezow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        //printf("Metoda Prostokatow. Proces nr-%d Pole = %f Wynik = %f\n", numer_proc, pole, result);
        if(numer_proc != 0){
            MPI_Send(&result, 1, MPI_DOUBLE, numer_proc-1, tag, MPI_COMM_WORLD); // 9
        }
    } 
    // 10
    MPI_Finalize();
    return 0;
```
### Result
Compare Java and MPI results
#### Java:
![image](https://user-images.githubusercontent.com/72127610/143480647-d8b13c5f-c39b-45cb-b59e-feefdd856e34.png)
#### MPI:
![z2_n](https://user-images.githubusercontent.com/72127610/143480979-65e65d66-499b-4082-abf2-9cd77b1b3163.jpg)


