! collin gros
! 09-28-2828
! cs471
! program #4
!
! code retrieved from:
! https://en.wikibooks.org/wiki/Fortran/Fortran_simple_input_and_output
!
!
! this program demonstrates how to get user input in fortran
!
program xproduct
	implicit none
	integer				:: i,j
	integer, parameter	:: out_unit=20

	print*,"enter two integers"
	read (*,*) i,j

	open (unit=out_unit,file="results.txt",action="write",status="replace")
	write (out_unit,*) "The product of",i," and",j
	write (out_unit,*) "is",i*j
	close (out_unit)
end program xproduct
