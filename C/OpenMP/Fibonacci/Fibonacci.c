#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int fib(int n);
int main(int argc,char *argv[])
{
int n=atoi(argv[1]);
#pragma omp parallel
{
   #pragma omp single
   printf("fib(%d)=%d\n",n,fib(n));
}
}
int fib(int n)
{
  int x,y;
  if(n<2)return n;
#pragma omp task shared(x)
  x = fib(n-1);
#pragma omp task shared(y)
  y = fib(n-2);
#pragma omp taskwait
  return (x+y);
}
