#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[3];
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
      A[0]=1;
      A[1]=2;
      A[2]=3;
      printf("rank=0,before A(%d,%d,%d)\n",A[0],A[1],A[2]);
    }

    if(rank==1)
    {
      A[0]=0;
      A[1]=0;
      A[2]=0;
      printf("rank=1,before A(%d,%d,%d)\n",A[0],A[1],A[2]);
    }
      MPI_Bcast(A,3,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
      printf("rank=0,after  A(%d,%d,%d)\n",A[0],A[1],A[2]);
    if(rank==1)
      printf("rank=1,after  A(%d,%d,%d)\n",A[0],A[1],A[2]);
    MPI_Finalize();
     
   return 0;
}

