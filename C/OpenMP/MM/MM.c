#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2000
	int A[N][N];
	int B[N][N];
	int C[N][N];

int main()
{
	int i,j,k;
	int res;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		A[i][j]=rand()%10;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		B[i][j]=rand()%10;
	for(i=0;i<N;i++)
	for(j=0;j<N;j++)
		C[i][j]=0;
#pragma omp parallel
	{
		printf("threads=%d\n",omp_get_num_threads());
	}
	double start =  omp_get_wtime();
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			res=0;
#pragma omp parallel for reduction(+:res)
			for(k=0;k<N;k++)
				res+=A[i][k]*B[k][j];
			C[i][j]=res;
		}
	double end = omp_get_wtime();
	printf("time = %lf C[%d][%d]=%d\n",end-start,N/2,N/2,C[N/2][N/2]);
	return 0;
}
