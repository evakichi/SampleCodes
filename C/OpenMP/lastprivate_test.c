#include<stdio.h>
#include<omp.h>

int main(int argc,char *argv[])
{
int a;
#pragma omp parallel for lastprivate(a)
   for(int i=0;i<8;i++)
   {
      a=i;
      printf("(before)I'm %d a=%d\n",omp_get_thread_num(),a);
   }
   printf("(after)a=%d\n",a);
 return 0;
}
