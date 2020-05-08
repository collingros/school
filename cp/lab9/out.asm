

.data

_L0:	.asciiz	"enter X"
_L1:	.asciiz	" x is "
NL:	.asciiz	"\n"


.align 2



.text

main:				# start of function
		subu $a0, $sp, 12		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $v0, 4		# printing a string
		la $a0, _L0		# printing the string by its label
		syscall		# system call for printing string
				
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		li $v0, 5		# read a number from input
		syscall		# reading a number
		sw $v0, ($a0)		# store a read into mem location
				
		li $v0, 4		# printing a string
		la $a0, _L1		# printing the string by its label
		syscall		# system call for printing string
				
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
				
		lw $ra, 4($sp)		# restore RA
		lw $sp, ($sp)		# restore SP
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
