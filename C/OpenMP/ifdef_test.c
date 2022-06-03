#include<stdio.h>
#include<unistd.h>

#ifdef _OPENMP
#include<omp.h>
#else
#endif

int main(int argc,char *argv[])
{
   int size;
#ifdef _OPENMP
#pragma omp parallel
{
   size=omp_get_num_threads();
}
#else
   size=1;
#endif

   printf("hello I have %d.\n",size);

   return 0;
}
