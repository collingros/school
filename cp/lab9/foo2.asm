

.data

NL:	.asciiz	"\n"


.align 2



.text

main:				# start of function
		subu $a0, $sp, 20		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		sw $a0, 16($sp)		# moving up to p for our assignment
		li $a0, 3		# expression is a NUMBER
		sw $a0, 12($sp)		# store s1 in temp
		li $a0, 5		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 12($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
		lw $t0, 16($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
				
				
		lw $ra, 4($sp)		# restore RA
		lw $sp, ($sp)		# restore SP
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
