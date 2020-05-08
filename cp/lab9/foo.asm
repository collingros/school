

.data

_L0:	.asciiz	"x[0] is: "
_L1:	.asciiz	"\n"
_L2:	.asciiz	"x[1] is: "
_L3:	.asciiz	"\n"
_L4:	.asciiz	"x[2] is: "
_L5:	.asciiz	"\n"
_L6:	.asciiz	"x[3] is: "
_L7:	.asciiz	"\n"
_L8:	.asciiz	"x[4] is: "
_L9:	.asciiz	"\n"
_L10:	.asciiz	"x[5] is: "
_L11:	.asciiz	"\n"
NL:	.asciiz	"\n"


.align 2

x:	.space	20


.text

main:				# start of function
		subu $a0, $sp, 28		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $a0, 0		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 8($sp)		# moving up to p for our assignment
		li $a0, 1		# expression is a NUMBER
		lw $t0, 8($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $a0, 1		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 12($sp)		# moving up to p for our assignment
		li $a0, 2		# expression is a NUMBER
		lw $t0, 12($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $a0, 2		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 16($sp)		# moving up to p for our assignment
		li $a0, 3		# expression is a NUMBER
		lw $t0, 16($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $a0, 3		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 20($sp)		# moving up to p for our assignment
		li $a0, 4		# expression is a NUMBER
		lw $t0, 20($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $a0, 4		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		sw $a0, 24($sp)		# moving up to p for our assignment
		li $a0, 5		# expression is a NUMBER
		lw $t0, 24($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		li $v0, 4		# printing a string
		la $a0, _L0		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 0		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L1		# printing the string by its label
		syscall		# system call for printing string
				
		li $v0, 4		# printing a string
		la $a0, _L2		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 1		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L3		# printing the string by its label
		syscall		# system call for printing string
				
		li $v0, 4		# printing a string
		la $a0, _L4		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 2		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L5		# printing the string by its label
		syscall		# system call for printing string
				
		li $v0, 4		# printing a string
		la $a0, _L6		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 3		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L7		# printing the string by its label
		syscall		# system call for printing string
				
		li $v0, 4		# printing a string
		la $a0, _L8		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 4		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L9		# printing the string by its label
		syscall		# system call for printing string
				
		li $v0, 4		# printing a string
		la $a0, _L10		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 5		# expression is a NUMBER
		move $a0, $a1		# move specified index to $a1
		la $a0, x		# id is a GLOBAL ARRAY
		add $a0, $sp, 0		# add offset to $a0
		add $a0, $a0, $a1		# add index to (array + offset
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
		li $v0, 4		# printing a string
		la $a0, _L11		# printing the string by its label
		syscall		# system call for printing string
				
				
		lw $ra, 4($sp)		# restore RA
		lw $sp, ($sp)		# restore SP
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
