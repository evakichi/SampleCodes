#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000000000

int main()
{
	double x,y;
	long i,count=0;
        srand48(time(NULL));	
	for(i = 0 ; i < N ; i++)
	{
		x = drand48();
		y = drand48();
		if(x*x+y*y<=1.0)
			count++;
	}
	printf("count=%ld\n",count);
	printf("pi = %lf\n",(double)(4.0*(double)count/(double)N));
}
