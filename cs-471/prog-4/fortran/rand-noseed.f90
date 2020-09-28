! collin gros
! 09-28-2828
! cs471
! program #4
!
! code retrieved from:
! 	https://gcc.gnu.org/onlinedocs/gfortran/RAND.html
!
!
! this program demonstrates the use of GNU rand() for generating
! random numbers in fortran. this will help me figure out how to
! prepare a random matrix for gaussian elmination in my assignment.
!
program test_rand
	integer,parameter :: seed = 86456
	
	call srand(seed)
	print *, rand(), rand(), rand(), rand()
	print *, rand(seed), rand(), rand(), rand()
end program test_rand
