#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

void print_column(int a[],int n);
void quick_sort(int a[],int p,int q);
void partition(int a[],int p,int q,int *jp,int *ip);
void swap(int *u,int *v);
int calc_omega(int size,int p);
int calc_rho(int p);
void marge_items(int *items,int p);
void find_pivots(int *items,int *pivots,int p,int rho);
void calc_blocks(int *column,int *pivots,int *start_pos,int *block_sizes,int p,int size);
void merge_exchanged_unsort(int *exchanged_unsort,int *pos,int *size,int p,int rank);
void check(int *answer,int *sorted,int n);

int main(int argc,char *argv[])
{
  int N=atoi(argv[1]);
  int size=N;
  int local_size;
  int i,j,n; 
  int rho,omega;
  int p;
  int rank;
  
  int *unsort,*unqsort,*sorted;
  int *local_unsort,*local_items,*items,*pivots;
  int *local_exchanged_unsort;
  int *partitions;
  int *start_pos,*block_sizes;
  int *block_strides;
  int *local_start_pos,*local_block_sizes;
  MPI_Status Status;


  double seq_start,seq_end;
  double start,end;


MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

local_size = N/p;
local_unsort=(int *)malloc(sizeof(int)*local_size);

  if(rank==0)
    printf("\n-----------------------------------------------------------\n"); 
  if(rank==0)
    printf("nodes=%d size=%d(%d per node)\n",p,N,local_size); 

srand((unsigned) time(NULL)*rank);

rho=calc_rho(p);
omega=calc_omega(size,p);
unsort=(int *)malloc(sizeof(int)*N);
unqsort=(int *)malloc(sizeof(int)*N);
sorted=(int *)malloc(sizeof(int)*N);
local_items=(int *)malloc(sizeof(int)*p);
items=(int *)malloc(sizeof(int)*p*p);
pivots=(int *)malloc(sizeof(int)*(p-1));
partitions=(int *)malloc(sizeof(int)*p);
start_pos=(int *)malloc(sizeof(int)*p);
block_sizes=(int *)malloc(sizeof(int)*p);
block_strides=(int *)malloc(sizeof(int)*p);
local_start_pos=(int *)malloc(sizeof(int)*p);
local_block_sizes=(int *)malloc(sizeof(int)*p);


   if(rank==0)
     for (i=0;i<N;i++)
      unsort[i]=unqsort[i]=rand()%N;
   
seq_start=MPI_Wtime();
  if (rank==0){
     quick_sort(unqsort,0,N-1);
   }
seq_end=MPI_Wtime();


start=MPI_Wtime();

  MPI_Scatter(unsort,local_size,MPI_INT,local_unsort,local_size,MPI_INT,0,MPI_COMM_WORLD);

   quick_sort(local_unsort,0,local_size-1);

   for(i=0;i<p;i++)
	*(local_items+i)=local_unsort[i*omega];
 
   MPI_Gather(local_items,p,MPI_INT,items,p,MPI_INT,0,MPI_COMM_WORLD);

   if(rank==0)
   {
     marge_items(items,p);     
     find_pivots(items,pivots,p,rho);
   }

   MPI_Bcast(pivots,(p-1),MPI_INT,0,MPI_COMM_WORLD);
   calc_blocks(local_unsort,pivots,start_pos,block_sizes,p,local_size);
   
   for(i=0;i<p;i++)
     MPI_Scatter(block_sizes,1,MPI_INT,local_block_sizes+i,1,MPI_INT,i,MPI_COMM_WORLD);
   
   *local_start_pos=0;
   n=0;
   for(i=1;i<p;i++)
     {
       *(local_start_pos+i)=n+*(local_block_sizes+i-1);
       n=*(local_start_pos+i);
     }
    
   n=(*(local_start_pos+p-1))+(*(local_block_sizes+p-1));

   local_exchanged_unsort=(int *)malloc(sizeof(int)*n);
   
   *block_strides=0;
   for(i=1;i<p;i++)
      *(block_strides+i)=(*(start_pos+i-1))+(*(block_sizes+i-1));
   for(i=0;i<p;i++)
      MPI_Scatterv(local_unsort,block_sizes,block_strides,MPI_INT,local_exchanged_unsort+(*(local_start_pos+i)),*(local_block_sizes+i),MPI_INT,i,MPI_COMM_WORLD);
   
   MPI_Barrier(MPI_COMM_WORLD);

   merge_exchanged_unsort(local_exchanged_unsort,local_start_pos,local_block_sizes,p,rank);
    
   MPI_Barrier(MPI_COMM_WORLD);

      MPI_Gather(&n,1,MPI_INT,block_sizes,1,MPI_INT,0,MPI_COMM_WORLD);
   if(rank==0)
   {
      *block_strides=0;
      for(i=1;i<p;i++)
         *(block_strides+i)=(*(block_strides+i-1))+(*(block_sizes+i-1));
   }

   MPI_Gatherv(local_exchanged_unsort,n,MPI_INT,sorted,block_sizes,block_strides,MPI_INT,0,MPI_COMM_WORLD);

end=MPI_Wtime();
   

   if(rank==0)
   {
      check(unqsort,sorted,N);
      printf("elapsed time=%e (seqential %e)  %3.2f times speedup.\n",(end-start),(seq_end-seq_start),(seq_end-seq_start)/(end-start));
      printf("-----------------------------------------------------------\n"); 
   }
   MPI_Finalize();
}

void check(int *answer,int *sorted,int n)
{
   int i;
   
   for(i=0;i<n;i++)
     if(answer[i]!=sorted[i])
     {
       printf("failed position %d\n",i);
       return;
     }
    printf("Check OK!\n");
}

void calc_blocks(int *column,int *pivots,int *start_pos,int *block_sizes,int p,int size)
{
  int i,j=0,n=0;

 *start_pos=0;

 for(i=0;i<size;i++)
   {
     if(*(column+i)>*(pivots+j))
	{
	 *(start_pos+j+1)=i;
         *(block_sizes+j)=i-*(start_pos+j);
         j++;
	}
     if(j==p-1)
      break;
   }
  *(block_sizes+j)=size-*(start_pos+j);
}

void find_pivots(int *items,int *pivots,int p,int rho)
{
  int i,j,k;
  for(i=1;i<p;i++)
    *(pivots+(i-1))=*(items+(p*i)+rho-1);
}

void merge_exchanged_unsort(int *exchanged_unsort,int *pos,int *size,int p,int rank)
{
  int i,j;
  int l,m,n,o;

  n=*(pos+p-1)+(*(size+p-1));
  int *sorted=(int *)malloc(sizeof(int)*n);

  for(i=0;i<n;i++)
   *(sorted+i)=*(exchanged_unsort+i);

  for(l=0;l<p-1;l++)
  {
    for(m=0;m<*(pos+l)+(*(size+l));m++)
      *(exchanged_unsort+m)=*(sorted+m); 
    
    o=*(pos+l+1);
    i=0;
    j=o;
    m=*(pos+l+1)+*(size+l+1);
    for(n=0;n<m;n++)
    {
      if((*(exchanged_unsort+i) < *(exchanged_unsort+j) && i < o) || j == m)
      {
        *(sorted+n)=*(exchanged_unsort+i);
        i++;
      }
      else
      {
        *(sorted+n)=*(exchanged_unsort+j);
        j++;
      }
    }
  }
    for(i=0;i<n;i++)
    {
      *(exchanged_unsort + i)= *(sorted + i);
    }

}

void marge_items(int *items,int p)
{
  int i,j,n;
  int l,m;
  int *sorted = (int *)malloc(sizeof(int)*p*p);
  
  for(i=0;i<p*p;i++)
   *(sorted+i)=*(items+i);

  for(l=0;l<p-1;l++)
  {
    for(m=0;m<p*(l+1);m++)
      *(items+m)=*(sorted+m); 
    
    n=0;
    i=0;
    j=(l+1)*p;
    for(n=0;n<(l+2)*p;n++)
    {
      if((*(items+i) < *(items+j) && i < (l+1)*p) || j == (l+2)*p)
      {
        *(sorted+n)=*(items+i);
        i++;
      }
      else
      {
        *(sorted+n)=*(items+j);
        j++;
      }
    }
  }
    for(i=0;i<p*p;i++)
    {
      *(items + i)= *(sorted + i);
    }
}

int calc_omega(int size,int p)
{
  return size/(p*p);
}

int calc_rho(int p)
{
  return p/2;
}

void print_column(int a[],int n)
{
   int i;
   for (i=0;i<n-1;i++)
   {
      printf("%ld,",a[i]);
   }
      printf("%ld\n",a[i]);
}

void quick_sort(int a[],int p,int q)
{
   int i,j;
   
   if(p < q)
   {
     partition(a,p,q,&j,&i);
     quick_sort(a,p,j);
     quick_sort(a,i,q);
   }
}

void partition(int a[],int p,int q,int *jp,int *ip)
{
   int i,j,s;
   
   i=p;
   j=q;
   s=a[p];
   while(i <= j){
     while(a[i]<s) ++i;
     while(a[j]>s) --j;
     if(i <= j){
       swap(&a[i],&a[j]);
       ++i;
       --j;
     }
   }
   *ip=i;
   *jp=j;
}

void swap(int *u,int *v)
{
   int tmp;
   tmp=*u;
   *u=*v;
   *v=tmp;
}
