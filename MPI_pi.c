#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define max 1000

long long int sum = 0, number_in_circle = 0;
double pi_estimate, distance_squared, x, y;

double rand_double(){
	return 2 * (rand() / (double)RAND_MAX - 1);
}

int main()
{
	
	int comm_sz, my_rank,q,i;
	long long int total_number_of_tosses,my_local_toss = 0;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	
	if(my_rank == 0){
		printf("Enter number of the total tosses: \n ");
		scanf("%lld",&total_number_of_tosses);

		while(total_number_of_tosses % comm_sz  != 0)
			total_number_of_tosses++;
		
		my_local_toss = total_number_of_tosses / comm_sz;
	}
	MPI_Bcast(&my_local_toss, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(my_rank != 0){
		for( i = 0; i <comm_sz; i++){
		  srand((long)time(NULL));
		  x = rand_double();
		  y = rand_double();
		  distance_squared = x * x + y * y;
		  if (distance_squared <= 1)
		  number_in_circle++;
		}
		MPI_Send(&number_in_circle,max,MPI_LONG_LONG_INT,0,0,MPI_COMM_WORLD);
		
	} else {
		MPI_Recv(&number_in_circle,max,MPI_LONG_LONG_INT,0, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("From process with x = %lld\n",  number_in_circle);
		MPI_Reduce(&number_in_circle,&sum,1, MPI_LONG_LONG_INT,MPI_SUM,0,MPI_COMM_WORLD);
			
	}
	
	pi_estimate = 4 * sum /(double)total_number_of_tosses;
	printf("Estimate pi = %f\n", pi_estimate);
	
	MPI_Finalize();
	return 0;
}

	
