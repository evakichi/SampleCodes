#include<stdio.h>
#include<immintrin.h>
#include<omp.h>

#define N 5000000
int aa[N*8],bb[N*8],cc[N*8];
__m256i a[N],b[N],c[N];
int main(int argc,char *argv[])
{
	int i,n;
	int *A,*B,*C;
	for(n=0;n<N;n++)
	{
		for(i=0;i<8;i++)
		{
			aa[i+n*8]=rand()%128;
			bb[i+n*8]=rand()%128;
		}
		a[n]=_mm256_set_epi32(aa[7+n*8],aa[6+n*8],aa[5+n*8],aa[4+n*8],aa[3+n*8],aa[2+n*8],aa[1+n*8],aa[0+n*8]);
		b[n]=_mm256_set_epi32(bb[7+n*8],bb[6+n*8],bb[5+n*8],bb[4+n*8],bb[3+n*8],bb[2+n*8],bb[1+n*8],bb[0+n*8]);
	}
	double A_wtime=omp_get_wtime();
	for(n=0;n<N;n++)
		for(i=0;i<8;i++)
			cc[i+n*8]=aa[i+n*8]+bb[i+n*8];
	A_wtime=omp_get_wtime()-A_wtime;
	double V_wtime=omp_get_wtime();
	for(n=0;n<N;n++)
		c[n]=_mm256_add_epi32(a[n],b[n]);
	V_wtime=omp_get_wtime()-V_wtime;
	for(n=0;n<N;n++)
	{
		A=(int*)&a[n];
		B=(int*)&b[n];
		C=(int*)&c[n];
		for(i=0;i<8;i++)
			if(C[i]!=cc[i+n*8])
				printf("(false)n=%5d,%3d,%3d=%3d+%3d\n",i+(8*n),cc[i+n*8],C[i],A[i],B[i]);
			/*
			 else
				printf("(ture) n=%5d,    %3d=%3d+%3d\n",i+(8*n),cc[i+n*8],C[i],A[i],B[i]);
			*/
	}
	printf("Array %lf,Vector %lf\n",A_wtime,V_wtime);
	return 0;
}
