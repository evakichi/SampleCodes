      program main
      include 'omp_lib.h'
      integer SIZE
      
      SIZE=8
!$omp parallel num_threads(SIZE)
      write(*,'("Hello I am ",i2)') omp_get_thread_num()
!$omp end parallel
      end
