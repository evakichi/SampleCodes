#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
    int A[6],B[3],S[3],D[3];
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
      S[0]=1;
      S[1]=2;
      S[2]=3;
      D[0]=0;
      D[1]=1;
      D[2]=3;
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
    if(rank==2)
    {
      for ( int i = 0 ; i < 6; i++)
        A[i]=0;
      B[0]=0;
      B[1]=0;
      B[2]=0;
      printf("rank=2,before A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    }
    MPI_Scatterv(A,S,D,MPI_INT,B,rank+1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
      printf("rank=0,after A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    if(rank==1)
      printf("rank=1,after A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    if(rank==2)
      printf("rank=2,after A(%d,%d,%d,%d,%d,%d),B(%d,%d,%d)\n",A[0],A[1],A[2],A[3],A[4],A[5],B[0],B[1],B[2]);
    MPI_Finalize();
     
   return 0;
}

