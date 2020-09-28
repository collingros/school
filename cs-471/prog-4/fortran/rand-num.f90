! collin gros
! 09-28-2828
! cs471
! program #4
!
! code retrieved from:
! https://gcc.gnu.org/onlinedocs/gfortran/RANDOM_005fNUMBER.html
!
!
! this program demonstrates the use of initializing rand with a random
! seed from data gathered from the os. this will make my program
! run with different numbers every time it is run.
!
program test_rn
	implicit none
	real::r
	call random_number(r)
	print *, r

	real::m(2,3)
	call random_number(m)
	print *, m
end program test_rn
