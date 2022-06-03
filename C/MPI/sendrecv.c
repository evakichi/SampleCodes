#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[3],B[3];
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
      B[0]=0;
      B[1]=0;
      B[2]=0;
      printf("rank=0,before A(%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2]);
      MPI_Sendrecv(A,3,MPI_INT,1,0,B,3,MPI_INT,1,1,MPI_COMM_WORLD,&status);
      printf("rank=0,after  A(%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2]);
    }
    if(rank==1)
    {
      A[0]=4;
      A[1]=5;
      A[2]=6;
      B[0]=0;
      B[1]=0;
      B[2]=0;
      printf("rank=1,before A(%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2]);
      MPI_Sendrecv(A,3,MPI_INT,0,1,B,3,MPI_INT,0,0,MPI_COMM_WORLD,&status);
      printf("rank=1,after  A(%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2]);
    }
    MPI_Finalize();
     
   return 0;
}

