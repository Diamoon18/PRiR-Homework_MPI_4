# PRiR-Homework_MPI_4
## Zadanie 1 - approximation of the value of PI
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



