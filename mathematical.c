#include <stdio.h>
#include <mpi.h>
float f(float x)
{
  return x * x;
}

int main()
{
  float a = 3, b = 6, h, approx, x_i, next_x_i, each_area;
  int i, n, my_rank, comm_sz;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  n = comm_sz - 1;
  h = (b - a)/n; 
  if(my_rank != 0)
  {
    i = my_rank;
    x_i = a + (i-1) * h;
    next_x_i = x_i + h;
    each_area = ((f(x_i) + f(next_x_i))/2)*h;
    MPI_Send(&each_area, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD); 
  }
  else 
  {
    approx = 0;
    for(i = 1; i <= n ; i++)
    {
      MPI_Recv(&each_area, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      approx += each_area;
    }
    printf("The area is: %f\n", approx);
  }
  MPI_Finalize();
  return 0;
}
