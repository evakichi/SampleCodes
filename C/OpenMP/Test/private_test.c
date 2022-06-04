#include<stdio.h>
#include<omp.h>

int main()
{
   int i,j,k=123,n;
#pragma omp parallel for private(j) firstprivate(k)
for(int l=0;l<8;l++)
   for(int m=0;m<1;m++)
    for(n=0;n<1;n++)
   {
      printf("(Before)hello I'm %d of %d (i,j,k,l,m,n)(%d,%d,%d,%d,%d,%d)\n",omp_get_thread_num(),omp_get_num_threads(),i,j,k,l,m,n);
      i=omp_get_thread_num();
      for(int o=0;o<10000000;o++);
      j=omp_get_thread_num();
      printf("(After) hello I'm %d of %d (i,j,k,l,m,n)(%d,%d,%d,%d,%d,%d)\n",omp_get_thread_num(),omp_get_num_threads(),i,j,k,l,m,n);
   }
   return 0;
}
