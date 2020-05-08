

.data

_L0:	.asciiz	"x[3] is: "
_L1:	.asciiz	"\n"
NL:	.asciiz	"\n"


.align 2

x:	.space	20


.text

main:				# start of function
		subu $a0, $sp, 12		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $a0, 3		# expression is a NUMBER
		move $a1, $a0		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 8($sp)		# moving up to p for our assignment
		li $a0, 100		# expression is a NUMBER
		lw $t0, 8($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $v0, 4		# printing a string
		la $a0, _L0		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 3		# expression is a NUMBER
		move $a1, $a0		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L1		# printing the string by its label
		syscall		# system call for printing string
				
				
		lw $ra, 4($sp)		# restore RA
		lw $sp, ($sp)		# restore SP
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
