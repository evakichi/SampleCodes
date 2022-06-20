#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
  int A[3]={0,0,0},B[6]={0,0,0,0,0,0};
  int rank,size;

  MPI_Init(&argc,&argv);

  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  for(int i = 0 ; i < 3 ; i++)
    A[i]=i+rank*3+1;

  printf("rank=%d,before A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",rank,A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
  MPI_Allgather(A,3,MPI_INT,B,3,MPI_INT,MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("rank=%d,after  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",rank,A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);

  MPI_Finalize();
    
  return 0;
}

