# MPI
**Note that all processes are executing the same program**. This is called **single program, multiple data** or **SPMD** in the parallel programming literature.<br><br>
<Strong>The format of the functions MPI_Send and MPI_Recv  are:<strong>

[Demo.c](https://github.com/Mira-Qiu/MPI/blob/master/MPI_Demo1.c)<br>
<strong>mpicc a.c</strong> : To compile this program enter<br>
<strong> mpiexec -n 5 ./a.out</strong>: To Execute this program for 5 processes enter <br>
mpicc -g -Wall a.c : To compile a C program more accurately and get all the possible errors.<br>
mpicc -g -Wall a.c -o aa: Have a different name for the executable file.<br><br>
