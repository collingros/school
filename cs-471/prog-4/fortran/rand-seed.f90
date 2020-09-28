! collin gros
! 09-28-2828
! cs471
! program #4
!
! code retrieved from:
! https://gcc.gnu.org/onlinedocs/gfortran/RANDOM_005fSEED.html
!
!
! this program demonstrates the use of initializing rand with a random
! seed from data gathered from the os. this will make my program
! run with different numbers every time it is run.
!
program test_random_seed
	implicit none
	integer, allocatable :: seed(:)
	integer :: n

	call random_seed(size = n)
	allocate(seed(n))
	call random_seed(get=seed)
	write (*, *) seed
end program test_random_seed
