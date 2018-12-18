#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>

#define ITERS 0
#define IN_CIRCLE 1

double randDouble();

int main(void)
{
    int comm_sz, my_rank, i, n;
    long long int iter, localInCircle = 0, inCircle;
    double x, y, ds, pi = 0;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    srandom((unsigned)time(NULL) + my_rank);
    n = comm_sz - 1;
    if (my_rank == 0) {
        printf("Enter the number of iterations.\n");
        scanf("%lld", &iter);
        for (; iter%n != 0; ++iter); // Make sure the number of iterations is divided by n
        for (i=0; i <= n; i++) {
            MPI_Send(&iter,  1, MPI_FLOAT, i, ITERS, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&iter, 1, MPI_FLOAT, 0, ITERS, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < iter/n; ++i)
        {
            x = randDouble();
            y = randDouble();
            ds = y*y + x*x;
            if (ds <= 1) {
                localInCircle++;
            }
        }
    }

    MPI_Reduce(&localInCircle,&inCircle,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if (my_rank == 0)
    {
        pi = (4 * inCircle) / (double)iter;
        printf("PI is: %f\n", pi);
    }
    MPI_Finalize();
    return 0;
}

double randDouble()
{
    return (double)rand() / (double)RAND_MAX ;
}
