#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10000000000

int main()
{
	struct drand48_data buf;
	double x,y;
	double start,end;
	long i,count=0;

	start = omp_get_wtime();
#pragma omp parallel private(x,y,buf)
{
	srand48_r(time(NULL)+omp_get_thread_num(),&buf);
	if(omp_get_thread_num()==0)
        	printf("Using %d core(s)\n",omp_get_num_threads());
#pragma omp for reduction(+:count)
	for(i = 0 ; i < N ; i++)
	{
		drand48_r(&buf,&x);
		drand48_r(&buf,&y);
		if(x*x+y*y<=1.0)
			count++;
	}
}
	end = omp_get_wtime();

#pragma omp parallel
{
	if(omp_get_thread_num()==0)
		printf("time = %lf, count = %ld , pi = %lf\n",end-start,count,(double)count/N*4);
}
}
