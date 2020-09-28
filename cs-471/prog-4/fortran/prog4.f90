! collin gros
! 09-28-2828
! cs471
! program #4
!
!
! this program performs gauss elimination with backwards substitution
! on a randomly generated matrix with a user-given size,
! and reports how long it takes to complete the gaussian elimination/subst
! part.
!
! input: size of matrix to do gauss elimination/ subst on
! output: time it took to compute gauss eliminatino/subst
!
! used all of the following as references:
! 	https://gcc.gnu.org/onlinedocs/gfortran/CPU_005fTIME.html
! 	Shaun Cooper's code on dynamic arrays in fortran
! 	https://labmathdu.wordpress.com/gaussian-elimination-without-pivoting/
! 	https://en.wikibooks.org/wiki/Fortran/Fortran_simple_input_and_output
! 	https://gcc.gnu.org/onlinedocs/gfortran/RAND.html
! 	https://gcc.gnu.org/onlinedocs/gfortran/RANDOM_005fNUMBER.html
! 	https://gcc.gnu.org/onlinedocs/gfortran/RANDOM_005fSEED.html
! 
program prog4
	implicit none

	integer::i,j,n
	real::tmp, start, finish, s
	! declare dynamic array
	real,dimension(:,:), allocatable::A
	real,dimension(:), allocatable::x

	! grab size from user input
	print *, "enter n: "
	read (*,*) n

	! allocate the arrays now that we know the sizes
	allocate(A(n, n+1))
	allocate(x(n))

	! iterate the array and fill with random numbers
	do i = 1, n
		do j = 1, n+1
			! assign every entry a random number between 0:100
			call random_number(tmp)
			A(i,j) = tmp * 100
		end do
	end do


	! start the clock
	call cpu_time(start)
		! perform guassian elimination
		do j = 1,n
			do i = j+1, n
				A(i,:)=A(i,:)-A(j,:)*A(i,j)/A(j,j)
			end do
		end do

		! perform backwards substitution
		do i = n,1,-1
			s=A(i, n+1)
			do j = i+1, n
				s=s-A(i, j) * x(j)
			end do
			x(i) = s/A(i, i)
		end do


	! stop the clock
	call cpu_time(finish)

	print *,"time: ", finish-start

end program prog4





