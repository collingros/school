! collin gros
! 09-28-2020
! cs471
!
! Shaun Cooper's code on dynamic arrays in fortran
!
	implicit none
	integer i,N,j
	real, dimension(:,:), allocatable :: A
 	real z
        N=10

	ALLOCATE(A(N,N))

	z=0	
   	do i = 1,10
         do j=1,10
	   A(i,j) = sqrt (1.0d0/i*j)
           z = z + A(i,j)
	   print *,z
 	  end do
        end do
        stop
	end 
