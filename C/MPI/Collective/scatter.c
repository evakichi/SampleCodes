#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[6],B[3];
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0)
    {
      for ( int i = 0 ; i < 6; i++)
        A[i]=i+1;
      B[0]=0;
      B[1]=0;
      B[2]=0;
      printf("rank=0,before A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    }
    if(rank==1)
    {
      for ( int i = 0 ; i < 6; i++)
        A[i]=0;
      B[0]=0;
      B[1]=0;
      B[2]=0;
      printf("rank=1,before A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    }
    MPI_Scatter(A,3,MPI_INT,B,3,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
      printf("rank=0,after A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    if(rank==1)
      printf("rank=1,after A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    MPI_Finalize();
     
   return 0;
}

