      program main
      include 'omp_lib.h'
      integer SIZE
      
      SIZE=8
!$omp parallel do num_threads(SIZE)
      do i = 1,SIZE
        write(*,'("Hello I am ",i2)') omp_get_thread_num()
      end do
      end
