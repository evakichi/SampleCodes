#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
  int A[3]={0,0,0},B[3]={0,0,0},SA[3]={0,0,0},DA[3]={0,0,0},SB[3]={0,0,0},DB[3]={0,0,0};
  int rank,size;
  
  MPI_Init(&argc,&argv);
  
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  
  if(rank==0)
  {
    A[0]=1;
    
    SA[0]=1;
    SA[1]=0;
    SA[2]=0;
    DA[0]=0;
    DA[1]=1;
    DA[2]=2;

    SB[0]=1;
    SB[1]=1;
    SB[2]=1;
    DB[0]=0;
    DB[1]=1;
    DB[2]=2;
  }

  if(rank==1)
  {
    A[0]=2;
    A[1]=3;
    
    SA[0]=1;
    SA[1]=1;
    SA[2]=0;      
    DA[0]=0;
    DA[1]=1;
    DA[2]=0;
    
    SB[0]=0;
    SB[1]=1;
    SB[2]=1;
    DB[0]=0;
    DB[1]=1;
    DB[2]=2;
  }

  if(rank==2)
  {
    A[0]=4;
    A[1]=5;
    A[2]=6;

    SA[0]=1;
    SA[1]=1;
    SA[2]=1;      
    DA[0]=0;
    DA[1]=1;
    DA[2]=2;

    SB[0]=0;
    SB[1]=0;
    SB[2]=1;
    DB[0]=0;
    DB[1]=1;
    DB[2]=2;
  }

  printf("rank=%d,before A(%d,%d,%d),B(%d,%d,%d)\n",rank,A[0],A[1],A[2],B[0],B[1],B[2]);
  MPI_Alltoallv(A,SA,DA,MPI_INT,B,SB,DB,MPI_INT,MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("rank=%d,after  A(%d,%d,%d),B(%d,%d,%d)\n",rank,A[0],A[1],A[2],B[0],B[1],B[2]);

  MPI_Finalize();
    
  return 0;
}

