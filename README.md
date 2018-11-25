# MPI
**Note that all processes are executing the same program**. This is called **single program, multiple data** or **SPMD** in the parallel programming literature.<br><br>
<Strong>The format of the functions MPI_Send and MPI_Recv  are:</strong>
 ```c
 #include <stdio.h>
#include <string.h>
#include <mpi.h> 

const int MAX_STRING = 100;

int main(void) 
{
   char       greeting[MAX_STRING];
   int        comm_sz;
   int        my_rank;
   int q;

   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank != 0) 
   { 
     sprintf (greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
     MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD); 
   } 
   else 
   {  
     printf("From myself: Greetings process %d of %d!\n", my_rank, comm_sz);
     for (q = 1; q < comm_sz; q++) 
     {
       MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       printf("Receiving from others: %s\n", greeting);
     } 
   }
   MPI_Finalize(); 

   return 0;
}
```

[Demo.c](https://github.com/Mira-Qiu/MPI/blob/master/MPI_Demo1.c)<br>
<strong>mpicc a.c</strong>          : To compile this program enter<br>
<strong> mpiexec -n 5 ./a.out</strong>: To Execute this program for 5 processes enter <br>
mpicc -g -Wall a.c                  : To compile a C program more accurately and get all the possible errors.<br>
mpicc -g -Wall a.c -o aa            : Have a different name for the executable file.<br><br>
