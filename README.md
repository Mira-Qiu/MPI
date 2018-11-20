# MPI
**Note that all processes are executing the same program**. This is called **single program, multiple data** or **SPMD** in the parallel programming literature.<br><br>
<Strong>The format of the functions MPI_Send and MPI_Recv  are:<strong>
```c
MPI_Send(vod* msg_buf_p, int msg_size, MPI_Data_type msg_type, int dest, int tag, MPI_Comm communicator)

MPI_Recv(vod* msg_buf_p, int buf_size, MPI_Data_type buf_type, int source, int tag, MPI_Comm communicator, MPI_Status* status_p)
```
