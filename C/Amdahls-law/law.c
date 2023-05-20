#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#define N 1024
float calc(float p,float n){return (1.0/((1.0-p)+(p/n)));}
int main()
{
 int i;
 printf("N\t1.0\t0.999\t0.99\t0.9\t0.5\t0.4\t0.2\t0.1\n");
 for(i=1;i<=N;i++)
 {
   printf("%4d\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",i,
                          calc(1.0,(float)i),
                          calc(0.999,(float)i),
                          calc(0.99,(float)i),
                          calc(0.9,(float)i),
                          calc(0.5,(float)i),
                          calc(0.4,(float)i),
                          calc(0.2,(float)i),
                          calc(0.1,(float)i));
 }
 return 0;
}

