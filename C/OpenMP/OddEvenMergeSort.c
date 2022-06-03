#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define MAX(a,b) ((a<b)?b:a)
#define MIN(a,b) ((a>=b)?b:a)

#define ODD(A,n,i) A[n+2*i]
#define EVEN(A,n,i) A[n+2*i+1]

void print_array(int *A,int l,int r)
{
    printf("\n");
    for(int i=l;i<r;i++)
	    printf("%3d ",i);
    printf("\n");
    for(int i=l;i<r;i++)
    	printf("%3d ",A[i]);
    printf("\n");
}

int *generate(int n)
{
    int *A=(int *)malloc(sizeof(int)*n);
    srand(time(NULL));
    for(int i=0;i<n;i++)
        A[i]=rand()%n;
    return A;
}

int *copy(int *A,int n)
{
    int *C=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        C[i]=A[i];
    return C;
}

int compare(const void *a,const void *b){return ( *(int *)a < *(int *)b )?0:1;}

void validate(int *A1,int *A2,int n){for(int i=0;i<n;i++)if(A1[i]!=A2[i]){printf("Failure\n");return;}printf("Success!\n");}


void odd_even_merge_sort_omp(int *A,int l,int c,int r);
void odd_even_merge_sort(int *A,int l,int c,int r);
void odd_even_merge(int *A,int l,int c,int r);
void odd_even_merge2(int *A,int s);

int log_2(int n){int i=0;while(n!=0){n=n>>1;i++;}return i-1;}

//int unsort[32]={2,3,18,9,23,11,4,25,0,13,6,21,14,27,1,10,15,5,16,17,8,24,22,12,19,29,26,30,28,7,31,20};
//int unsort_array[16]={2,3,9,11,4,13,6,14,1,10,15,5,16,8,12,7};
//int unsort_array[8]={2,3,4,6,1,5,8,7};

int main(int argc,char* argv[])
{
    char *n="32";
    int N=atoi(argc==2?argv[1]:n);

    int *unpsort=generate(N);
    int *unqsort=copy(unpsort,N);

    double odd_even_parallel_t = omp_get_wtime();
    odd_even_merge_sort_omp(unpsort,0,N/2,N);
    odd_even_parallel_t = omp_get_wtime()-odd_even_parallel_t;

    double qsort_t = omp_get_wtime();
    qsort(unqsort,N,sizeof(int),&compare);
    qsort_t=omp_get_wtime()-qsort_t;

    validate(unpsort,unqsort,N);
    printf("qsort=%lf,Parallel = %lf sec (%lf times speedup)\n",
    qsort_t,
    odd_even_parallel_t,(qsort_t/odd_even_parallel_t));
    return 0;
}

void odd_even_merge(int *A,int l,int c,int r)
{

    int n=c-l;
    int N=n/2;

    int *D=(int *)malloc(sizeof(int)*n);
    int *E=(int *)malloc(sizeof(int)*n);

    int t0=0,t1=0;
    for(int i=0;i<n;i++)
    {
        if( t0 == N || ( t1 != N && ODD(A,l,t0) > ODD(A,c,t1) ) )
            D[i]=ODD(A,c,t1++);
        else
            D[i]=ODD(A,l,t0++);
    }
    int t2=0,t3=0;
    for(int i=0;i<n;i++)
    {
        if( t2 == N || ( t3 != N && EVEN(A,l,t2) > EVEN(A,c,t3)) )
            E[i]=EVEN(A,c,t3++);
        else
            E[i]=EVEN(A,l,t2++);
    }


    A[l]=D[0];
    for(int i=1;i<n;i++)
    {
        A[l+2*i-1]=MIN(D[i],E[i-1]);
        A[l+2*i]=MAX(D[i],E[i-1]);
    }
    A[r-1]=E[n-1];

    free(D);
    free(E);
}

void odd_even_merge2(int *A,int s)
{
    int TMP[4]={A[s+0],A[s+1],A[s+2],A[s+3]};
    A[s+0]=MIN(MIN(TMP[0],TMP[1]),MIN(TMP[2],TMP[3]));
    A[s+1]=MIN(MAX(MIN(TMP[0],TMP[1]),MIN(TMP[2],TMP[3])),MIN(MAX(TMP[0],TMP[1]),MAX(TMP[2],TMP[3])));
    A[s+2]=MAX(MAX(MIN(TMP[0],TMP[1]),MIN(TMP[2],TMP[3])),MIN(MAX(TMP[0],TMP[1]),MAX(TMP[2],TMP[3])));
    A[s+3]=MAX(MAX(TMP[0],TMP[1]),MAX(TMP[2],TMP[3]));
}

void odd_even_merge_sort(int *A,int l,int c,int r)
{

    if(r-l==4)
    {
        odd_even_merge2(A,l);
        return;        
    }
    if(c-l==4)
    {
        odd_even_merge2(A,l);
        odd_even_merge2(A,c); 
        odd_even_merge(A,l,c,r);
        return;
    }
    odd_even_merge_sort(A,l,(l+c)/2,c);
    odd_even_merge_sort(A,c,(c+r)/2,r);
    odd_even_merge(A,l,c,r);
}

void odd_even_merge_sort_omp(int *A,int l,int c,int r)
{
    int j=1;
    int size;
    #pragma omp parallel shared(size)
    {
        size = omp_get_num_threads();
    }
    for(int i = size ; i > 1 ; i=i/2)
    {
        if(j==1)
        {
            #pragma omp parallel for shared(A,size) firstprivate(l,c,r)
            for(int k=0; k < i ; k++)
            {
                int L=k*(r/size)*j;
                int R=(k+1)*(r/size)*j;
                int C=(L+R)/2;
                odd_even_merge_sort(A,L,C,R);
            }
        }
        else
        {
            #pragma omp parallel for shared(A,size) firstprivate(l,c,r) 
            for(int k=0; k < i ; k++)
            {
                int L=k*(r/size)*j;
                int R=(k+1)*(r/size)*j;
                int C=(L+R)/2;
                odd_even_merge(A,L,C,R);
            }
        }
        j=j<<1;
    }
    odd_even_merge(A,l,c,r);
}
