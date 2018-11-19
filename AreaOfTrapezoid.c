#include <stdio.h>
#define SIDE 0
#define HEIGHT 1

int main()
{
  float side1, side2, height;
  int comm_sz, my_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0)
  {
    printf("Enter three numbers for the sides and the height of a trapezoid.\n");
    scanf("%f%f%f", &side1, &side2, &height);

    MPI_Send(&side1,  1, MPI_FLOAT, 1, SIDE,   MPI_COMM_WORLD);
    MPI_Send(&side2,  1, MPI_FLOAT, 1, SIDE,   MPI_COMM_WORLD);
    MPI_Send(&height, 1, MPI_FLOAT, 1, HEIGHT, MPI_COMM_WORLD);
  }
  else 
  { 
    MPI_Recv(&height, 1, MPI_FLOAT, 0, HEIGHT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&side2,  1, MPI_FLOAT, 0, SIDE,   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&side1,  1, MPI_FLOAT, 0, SIDE,   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Height = %.2f, side1 = %.2f, side2 = %.2f\n", height, side1, side2);
    printf("The area of trapezoid is: %.2f\n", (side1 + side2)/2 * height);
  }
  MPI_Finalize();
}

/*  This program the processor with the rank: 0 sends three numbers to the processor with rank: 
*   1 to calculate the area of a trapezoid. The first two numbers are for the sides and the 
*   third number is for the height.
*/
