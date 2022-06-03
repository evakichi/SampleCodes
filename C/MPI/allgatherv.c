#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[3],B[6],S[3]={1,2,3},D[3]={0,1,3};
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0)
    {
      A[0]=1;
      A[1]=0;
      A[2]=0;
      for ( int i = 0 ; i < 6; i++)
        B[i]=0;
      printf("rank=0,before A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    }
    if(rank==1)
    {
      A[0]=2;
      A[1]=3;
      A[2]=0;
      for ( int i = 0 ; i < 6; i++)
        B[i]=0;
      printf("rank=1,before  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    }
    if(rank==2)
    {
      A[0]=4;
      A[1]=5;
      A[2]=6;
      for ( int i = 0 ; i < 6; i++)
        B[i]=0;
      printf("rank=2,before  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    }
    MPI_Allgatherv(A,rank+1,MPI_INT,B,S,D,MPI_INT,MPI_COMM_WORLD);
    if(rank==0)
        printf("rank=0,after  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    if(rank==1)
        printf("rank=1,after  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    if(rank==2)
        printf("rank=2,after  A(%d,%d,%d),B(%d,%d,%d,%d,%d,%d)\n",A[0],A[1],A[2],B[0],B[1],B[2],B[3],B[4],B[5]);
    MPI_Finalize();
     
   return 0;
}

