#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
int main(int argc,char *argv[])
{
 const size_t len = 16;
  __m512 a,b;
 float c[len];
 for (int i=0;i<len;i++)
 {
    a[i]=(float)rand()/RAND_MAX;
    b[i]=(float)rand()/RAND_MAX;
 }
 __m512 ps = _mm512_add_ps(a,b);
 _mm512_storeu_ps(c,ps);
 for (int i=0 ;i< len;i++)
 printf("%f=%f+%f\n",c[i],a[i],b[i]); 
}
