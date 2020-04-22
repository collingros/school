

.data

NL:	.asciiz	"\n"


.align 2



.text

main:				# start of function
		subu $a0, $sp, 0		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		lw $ra, 4($a0)		# restore RA
		lw $sp, 4($sp)		# restore RA
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
