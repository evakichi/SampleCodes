#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000000

int main(int argc,char* argv[])
{
	double x,y;
	double start,end;
	long i;
	long count=0,last=0;
	long n;
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	srand48(time(NULL)+rank);
	if(rank==0)
        	printf("Using %d core(s)\n",size);
	start = MPI_Wtime();
	n = N/size;
	for(i = 0 ; i < n ; i++)
	{
		x = drand48();
		y = drand48();
		if(x*x+y*y<=1.0)
			count++;
	}
	MPI_Reduce(&count,&last,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
	end = MPI_Wtime();
	if(rank==0)
		printf("time = %lf , count = %lf , pi = %lf\n",end-start,(double)last,(double)(4.0*(double)last/(double)N));
	MPI_Finalize();
	return 0;
}
