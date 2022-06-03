#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(int argc,char *argv[])
{
   double time=omp_get_wtime();
#pragma omp parallel for schedule(dynamic,2)
   for(int i=1;i<=12;i++)
   {
     sleep(i);
     printf("I'm %d finish %02d iter\n",omp_get_thread_num(),i);
   }
   printf("total %lf sec\n",omp_get_wtime()-time);
   return 0;
}
