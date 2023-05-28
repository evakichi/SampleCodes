#include<stdio.h>
#include<omp.h>
int main(int argc,char *argv[])
{
#pragma omp parallel
	{
		int me = omp_get_thread_num();
		int all = omp_get_num_threads();
		printf("Hello I'm %d of %d\n",me,all);
	}
	return 0;
}
