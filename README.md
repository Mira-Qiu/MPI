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

```c
MPI_Init(NULL, NULL)
```
This is sililar to the function: initialize() for the Sequent Simulater. <br>
The prototype(signature, first line of the definition of a funciton) is the format of :<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**int MPI_Init(int \*argc, char \*\*\*argv)**<br>
**argc** accepts the address of an integer location and **argv** accepts the address of an array of strings.<br>
<li>(int argc, char\*\* argv) argc accepts an integer and argv accepts an array of strings. But in: (int\* argc, char\*\*\* argv) argc accepts the address of an integer location and argv accepts the address of an array of strings.</li><br>
<li><strong>MPI_Init</strong> does all the necessary setups such as creating a message buffer (i.e. array of characters), giving ranks(0,1,2...) to the processes.<br></li><br>

```c
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz)
```
<li>This is similar to the function: m_set_procs(...) in the Sequent Simulator. <strong>comm_sz</strong> is the number of the processes we like to create. For the above execution: <strong> mpiexec -n 5 ./a.out </strong>the value of the variable is : 5.<br></li>
<strong>Note: Do not give any number to the variables: myRank, and comm_sz in the programm. It is at run time that you give a number.</strong>

```c
int MPI_Comm_size(MPI_Comm comm, int* comm_sz_p)
```

The first parameter is of type MPI_Comm which is a predefined data type and the second parameter accepts the address of an integer location.<br>
```c
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank)
```
This is similar to the function: m_get_myid() in the Sequent Simulator.This funcion obtains the rank of the running process which would be the content of the parameter: my_rank.<br>

```c
//if-part
  sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
  MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
```
The build-in function: sprintf gives a string to the array(greeting).

