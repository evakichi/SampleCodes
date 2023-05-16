#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1200
	int A[N][N];
	int B[N][N];
	int C[N][N];

int main()
{
	int i,j,k;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		A[i][j]=rand()%10;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		B[i][j]=rand()%10;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		C[i][j]=0;
	double start =  omp_get_wtime();
#pragma acc kernels
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			for(k=0;k<N;k++)
				C[i][j]+=A[i][k]*B[k][j];
	double end = omp_get_wtime();
	printf("time = %lf C[%d][%d]=%d\n",end-start,N/2,N/2,C[N/2][N/2]);
	return 0;
}
