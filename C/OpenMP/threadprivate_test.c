#include<stdio.h>
#include<omp.h>
int tp;
#pragma omp threadprivate(tp)

int main(int argc,char *argv[])
{

    #pragma omp parallel
    {
        printf("(Before 0)hello I'm %d of %d.\n",tp,omp_get_num_threads());
        tp = omp_get_thread_num();
        printf("(After  0)hello I'm %d of %d.\n",tp,omp_get_num_threads());
    }
    #pragma omp parallel copyin(tp)
    {
        printf("(After  1)hello I'm %d of %d.\n",tp,omp_get_num_threads());
    }
    return 0;
}
