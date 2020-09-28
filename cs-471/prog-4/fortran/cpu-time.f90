! collin gros
! 09-28-2828
! cs471
! program #4
!
! code retrieved from:
! https://gcc.gnu.org/onlinedocs/gfortran/CPU_005fTIME.html
!
!
! this program demonstrates how to time a section of code in fortran.
! i will use this in my main program {prog4.f90} to give me execution
! time to compare with python.
!
program test_cpu_time
	real :: start, finish
	call cpu_time(start)
		! put code to test here
	call cpu_time(finish)
	print '("Time = ",f6.3," seconds.")',finish-start
end program test_cpu_time
