#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
  int A[6]={0,0,0,0,0,0},B[3]={0,0,0},S[3]={0,0,0},D[3]={0,0,0};
  int rank,size;
  
  MPI_Init(&argc,&argv);
  
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  if(rank==0)
  {
    for ( int i = 0 ; i < 6; i++)
      A[i]=i+1;
    S[0]=1;
    S[1]=2;
    S[2]=3;
    D[0]=0;
    D[1]=1;
    D[2]=3;
  }

  printf("rank=%d,before A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",rank,A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
  MPI_Scatterv(A,S,D,MPI_INT,B,rank+1,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("rank=%d,after  A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",rank,A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);

  MPI_Finalize();
    
  return 0;
}

