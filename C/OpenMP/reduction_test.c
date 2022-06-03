#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(int argc,char *argv[])
{
   double time=omp_get_wtime();
   int sum=0;
   for(int i=0;i<omp_get_max_threads();i++)
   {
     sleep(i);
     sum+=i;
     printf("finish %d iter\n",i);
   }
   printf("total %d %lf sec\n",sum,omp_get_wtime()-time);
   time=omp_get_wtime();
   sum=0;
#pragma omp parallel for reduction(+:sum)
   for(int i=0;i<8;i++)
   {
     sleep(i);
     sum+=i;
     printf("finish %d iter\n",i);
   }
   printf("total %d %lf sec\n",sum,omp_get_wtime()-time);
   return 0;
}
