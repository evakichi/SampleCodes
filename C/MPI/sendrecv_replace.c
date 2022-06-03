#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[3];
    int rank,size;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
      A[0]=1;
      A[1]=2;
      A[2]=3;
    }
    if(rank==1)
    {
      A[0]=4;
      A[1]=5;
      A[2]=6;
    }     
    if(rank==2)
    {
      A[0]=7;
      A[1]=8;
      A[2]=9;
    }     
      printf("rank=%d,before A(%d,%d,%d)\n",rank,A[0],A[1],A[2]);
      MPI_Sendrecv_replace(A,3,MPI_INT,(rank+1)%size,rank,(rank+size-1)%size,(rank+size-1)%size,MPI_COMM_WORLD,&status);
      printf("rank=%d,after  A(%d,%d,%d)\n",rank,A[0],A[1],A[2]);
    MPI_Finalize();
     
   return 0;
}

