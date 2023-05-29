#include<stdio.h>
#include<immintrin.h>

int main(int argc,char *argv[])
{
	__m256i a,b,c;
	__m256i mask;
	int i;
	a=_mm256_set_epi32(rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256);
	b=_mm256_set_epi32(rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256,rand()%256);
	mask=_mm256_set_epi32(0,0,0,0,0,0,0,0);
	c=_mm256_add_epi32(a,b);
	int* A=(int*)&a;
	int *B=(int*)&b;
	int *res=(int*)&c;
	for(i=0;i<8;i++)
		printf("c[%d](%d)=a[%d](%d)+b[%d](%d)\n",i,res[i],i,A[i],i,B[i]);
	return 0;
}
