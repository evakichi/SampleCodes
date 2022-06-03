#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(int argc,char *argv[])
{
   double time=omp_get_wtime();
   for(int i=1;i<=8;i++)
   {
     sleep(i);
     printf("finish %02d iter\n",i);
   }
   printf("total %lf sec\n",omp_get_wtime()-time);
   time=omp_get_wtime();
#pragma omp parallel for
   for(int i=1;i<=8;i++)
   {
     sleep(i);
     printf("finish %02d iter\n",i);
   }
   printf("total %lf sec\n",omp_get_wtime()-time);
   return 0;
}
