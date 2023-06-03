#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int fib(int n);

int main(int argc,char *argv[])
{
	int n=atoi(argv[1]);
#pragma omp parallel sections
{
	printf("fib(%d)=%d\n",n,fib(n));
}
	return 0;
}

int fib(int n)
{
	int x,y;
	if(n<2)return n;
#pragma omp section shared(x)
	x = fib(n-1);
#pragma omp section shared(y)
	y = fib(n-2);
#pragma omp wait
	return (x+y);
}
