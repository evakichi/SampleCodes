#include<stdio.h>
#include<mpi.h>

int main(int argc,char *argv[])
{
  int A[3]={0,0,0};
  int rank,size;

  MPI_Init(&argc,&argv);
  
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  
  if(rank==0)
    for(int i = 0 ; i < 3 ; i++)
      A[i]=i+rank*3+1;
  MPI_Barrier(MPI_COMM_WORLD);
 
  printf("rank=%d,before A(%d,%d,%d)\n",rank,A[0],A[1],A[2]);
  MPI_Bcast(A,3,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  printf("rank=%d,after  A(%d,%d,%d)\n",rank,A[0],A[1],A[2]);

  MPI_Finalize();
    
  return 0;
}
