#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define N 10000000000

int main()
{
   long int i,alpha=0;
   double x,y;
   double start=omp_get_wtime();
#pragma omp parallel   
{
   srand48(time(NULL)+omp_get_thread_num());
#pragma omp for reduction(+:alpha)
   for(i=0;i<N;i++)
   {
      x=drand48();
      y=drand48();
      if(x*x+y*y<=1.0)alpha++;
   } 
}
   printf("Time=%lf(sec) N=%ld PI=%lf\n",omp_get_wtime()-start,N,(double)4*alpha/N);
   return 0;
}
