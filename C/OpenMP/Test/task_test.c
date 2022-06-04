#include<stdio.h>
#include<unistd.h>
#include<omp.h>

int main(int argc,char *argv[])
{
#pragma omp parallel sections
{
   #pragma omp section
   {
      sleep(10);
      printf("finish 10sec section\n");
   }
   #pragma omp section
   {
      sleep(5);
      printf("finish 5sec section\n");
   }
   #pragma omp section
   {
      sleep(3);
      printf("finish 3sec section\n");
   }
}
#pragma omp parallel
{
   #pragma omp single
   {
      #pragma omp task
      {
         sleep(10);
         printf("finish 10sec task\n");
      }
      #pragma omp task
      {
         sleep(5);
         printf("finish 5sec task\n");
      }
      #pragma omp task
      {
         sleep(3);
         printf("finish 3sec task\n");
      }
  }
}
   return 0;
}
