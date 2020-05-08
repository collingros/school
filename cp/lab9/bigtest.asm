

.data

_L0:	.asciiz	"begin\n"
_L1:	.asciiz	"\nthe contents of globArr is: \n"
_L2:	.asciiz	"\nthe contents of locArr is: \n"
_L3:	.asciiz	"\nbegin expression tests\n"
_L12:	.asciiz	"enter something: "
_L13:	.asciiz	"\nyou entered: "
_L16:	.asciiz	"exit\n"
_L14:	.asciiz	"pass\n"
_L15:	.asciiz	"fail\n"
_L10:	.asciiz	"fail\n"
_L11:	.asciiz	"pass\n"
_L8:	.asciiz	"pass\n"
_L9:	.asciiz	"fail\n"
_L6:	.asciiz	"fail\n"
_L7:	.asciiz	"pass\n"
_L4:	.asciiz	"pass\n"
_L5:	.asciiz	"fail\n"
NL:	.asciiz	"\n"


.align 2

globArr:	.space	12
globX:	.space	4


.text

main:				# start of function
		subu $a0, $sp, 120		# adjust the stack for function setup
		sw $sp, ($a0)		
		sw $ra, 4($a0)		
		move $sp, $a0		# adjust the stack pointer
				
		li $v0, 4		# printing a string
		la $a0, _L0		# printing the string by its label
		syscall		# system call for printing string
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 40($sp)		# moving up to p for our assignment
		li $a0, 0		# expression is a NUMBER
		lw $t0, 40($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
_L18:				# begin of while statement
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 44($sp)		# store s1 in temp
		li $a0, 3		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 44($sp)		# put temp in $a0
		slt $a0, $a0, $a1		# expr <
				
		li $t0, 0		# while conditional
		beq $a0, $t0, _L17		# if they're both 0 we want to jump to end
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# move specified index to $a1
		sll $a1, $a1, 2		# offset needs to be moevd by WSIZE
		la $a0, globArr		# id is a GLOBAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		sw $a0, 52($sp)		# moving up to p for our assignment
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 48($sp)		# store s1 in temp
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 48($sp)		# put temp in $a0
		mult $a0, $a1		# expr MULTIPLY
		mflo $a0		# expr MULTIPLY
				
		lw $t0, 52($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 60($sp)		# moving up to p for our assignment
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 56($sp)		# store s1 in temp
		li $a0, 1		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 56($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		lw $t0, 60($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		j _L18		# repeat loop
_L17:				# end of while statement
		li $v0, 4		# printing a string
		la $a0, _L1		# printing the string by its label
		syscall		# system call for printing string
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 48($sp)		# moving up to p for our assignment
		li $a0, 0		# expression is a NUMBER
		lw $t0, 48($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
_L20:				# begin of while statement
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 52($sp)		# store s1 in temp
		li $a0, 3		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 52($sp)		# put temp in $a0
		slt $a0, $a0, $a1		# expr <
				
		li $t0, 0		# while conditional
		beq $a0, $t0, _L19		# if they're both 0 we want to jump to end
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# move specified index to $a1
		sll $a1, $a1, 2		# offset needs to be moevd by WSIZE
		la $a0, globArr		# id is a GLOBAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
		li $v0, 4		# printing a string
		la $a0, NL		# print newline
		syscall		# system call for printing string
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 60($sp)		# moving up to p for our assignment
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 56($sp)		# store s1 in temp
		li $a0, 1		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 56($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		lw $t0, 60($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		j _L20		# repeat loop
_L19:				# end of while statement
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 56($sp)		# moving up to p for our assignment
		li $a0, 0		# expression is a NUMBER
		lw $t0, 56($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
_L22:				# begin of while statement
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 60($sp)		# store s1 in temp
		li $a0, 5		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 60($sp)		# put temp in $a0
		slt $a0, $a0, $a1		# expr <
				
		li $t0, 0		# while conditional
		beq $a0, $t0, _L21		# if they're both 0 we want to jump to end
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# move specific index to $a1
		sll $a1, $a1, 2		# offset needs to be moved by WSIZE
		add $a0, $sp, 20		# id is a LOCAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		sw $a0, 68($sp)		# moving up to p for our assignment
		li $a0, 2		# expression is a NUMBER
		sw $a0, 64($sp)		# store s1 in temp
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 64($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		lw $t0, 68($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 76($sp)		# moving up to p for our assignment
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 72($sp)		# store s1 in temp
		li $a0, 1		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 72($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		lw $t0, 76($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		j _L22		# repeat loop
_L21:				# end of while statement
		li $v0, 4		# printing a string
		la $a0, _L2		# printing the string by its label
		syscall		# system call for printing string
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 64($sp)		# moving up to p for our assignment
		li $a0, 0		# expression is a NUMBER
		lw $t0, 64($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
_L24:				# begin of while statement
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 68($sp)		# store s1 in temp
		li $a0, 5		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 68($sp)		# put temp in $a0
		slt $a0, $a0, $a1		# expr <
				
		li $t0, 0		# while conditional
		beq $a0, $t0, _L23		# if they're both 0 we want to jump to end
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# move specific index to $a1
		sll $a1, $a1, 2		# offset needs to be moved by WSIZE
		add $a0, $sp, 20		# id is a LOCAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
		li $v0, 4		# printing a string
		la $a0, NL		# print newline
		syscall		# system call for printing string
				
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		sw $a0, 76($sp)		# moving up to p for our assignment
		add $a0, $sp, 16		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 72($sp)		# store s1 in temp
		li $a0, 1		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 72($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		lw $t0, 76($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		j _L24		# repeat loop
_L23:				# end of while statement
		li $v0, 4		# printing a string
		la $a0, _L3		# printing the string by its label
		syscall		# system call for printing string
				
		li $a0, 1		# expression is a NUMBER
		sw $a0, 72($sp)		# store s1 in temp
		li $a0, 2		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 72($sp)		# put temp in $a0
		add $a0, $a0, $a1		# expr PLUS
				
		sw $a0, 76($sp)		# store s1 in temp
		li $a0, 2		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 76($sp)		# put temp in $a0
		sne $a0, $a0, $a1		# expr !=
				
		li $t0, 0		# begin of if statement
		beq $a0, $t0, _L25		# if they're both 0 we want to jump to else
		li $v0, 4		# printing a string
		la $a0, _L4		# printing the string by its label
		syscall		# system call for printing string
				
		j _L26		# end of positive part of if statement
_L25:				# begin negative part of if statement
		li $v0, 4		# printing a string
		la $a0, _L5		# printing the string by its label
		syscall		# system call for printing string
				
_L26:				# end of if statement
		li $a0, 0		# expression is a NUMBER
		move $a1, $a0		# move specified index to $a1
		sll $a1, $a1, 2		# offset needs to be moevd by WSIZE
		la $a0, globArr		# id is a GLOBAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 80($sp)		# store s1 in temp
		li $a0, 0		# expression is a NUMBER
		move $a1, $a0		# move specific index to $a1
		sll $a1, $a1, 2		# offset needs to be moved by WSIZE
		add $a0, $sp, 20		# id is a LOCAL ARRAY
		add $a0, $a0, $a1		# add index (array + offset)
				
		lw $a0, ($a0)		# fetch value for ID
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 80($sp)		# put temp in $a0
		sgt $a0, $a0, $a1		# expr >
				
		li $t0, 0		# begin of if statement
		beq $a0, $t0, _L27		# if they're both 0 we want to jump to else
		li $v0, 4		# printing a string
		la $a0, _L6		# printing the string by its label
		syscall		# system call for printing string
				
		j _L28		# end of positive part of if statement
_L27:				# begin negative part of if statement
		li $v0, 4		# printing a string
		la $a0, _L7		# printing the string by its label
		syscall		# system call for printing string
				
_L28:				# end of if statement
		li $a0, 0		# expression is FALSE
		sltiu $a0, $a0, 1		# expr !
				
		li $t0, 0		# begin of if statement
		beq $a0, $t0, _L29		# if they're both 0 we want to jump to else
		li $v0, 4		# printing a string
		la $a0, _L8		# printing the string by its label
		syscall		# system call for printing string
				
		j _L30		# end of positive part of if statement
_L29:				# begin negative part of if statement
		li $v0, 4		# printing a string
		la $a0, _L9		# printing the string by its label
		syscall		# system call for printing string
				
_L30:				# end of if statement
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		sw $a0, 104($sp)		# moving up to p for our assignment
		li $a0, 8		# expression is a NUMBER
		sw $a0, 88($sp)		# store s1 in temp
		li $a0, 2		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 88($sp)		# put temp in $a0
		mult $a0, $a1		# expr MULTIPLY
		mflo $a0		# expr MULTIPLY
				
		sw $a0, 92($sp)		# store s1 in temp
		li $a0, 4		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 92($sp)		# put temp in $a0
		div $a0, $a1		# expr DIVIDE
		mflo $a0		# expr DIVIDE
				
		sw $a0, 100($sp)		# store s1 in temp
		li $a0, 4		# expression is a NUMBER
		sw $a0, 96($sp)		# store s1 in temp
		li $a0, 2		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 96($sp)		# put temp in $a0
		sub $a0, $a0, $a1		# expr MINUS
				
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 100($sp)		# put temp in $a0
		mult $a0, $a1		# expr MULTIPLY
		mflo $a0		# expr MULTIPLY
				
		lw $t0, 104($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		add $a0, $sp, 8		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		sw $a0, 108($sp)		# store s1 in temp
		li $a0, 8		# expression is a NUMBER
		move $a1, $a0		# moving expr1 out of the way
		lw $a0, 108($sp)		# put temp in $a0
		seq $a0, $a0, $a1		# expr ==
				
		sltiu $a0, $a0, 1		# expr !
				
		li $t0, 0		# begin of if statement
		beq $a0, $t0, _L31		# if they're both 0 we want to jump to else
		li $v0, 4		# printing a string
		la $a0, _L10		# printing the string by its label
		syscall		# system call for printing string
				
		j _L32		# end of positive part of if statement
_L31:				# begin negative part of if statement
		li $v0, 4		# printing a string
		la $a0, _L11		# printing the string by its label
		syscall		# system call for printing string
				
_L32:				# end of if statement
		li $v0, 4		# printing a string
		la $a0, _L12		# printing the string by its label
		syscall		# system call for printing string
				
		la $a0, globX		# id is a GLOBAL SCALAR
				
		li $v0, 5		# read a number from input
		syscall		# reading a number
		sw $v0, ($a0)		# store a read into mem location
				
		li $v0, 4		# printing a string
		la $a0, _L13		# printing the string by its label
		syscall		# system call for printing string
				
		la $a0, globX		# id is a GLOBAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		li $v0, 1		# printing a number
		syscall		# system call for print number
		li $v0, 4		# printing a string
		la $a0, NL		# print newline
		syscall		# system call for printing string
				
		add $a0, $sp, 12		# id is a LOCAL SCALAR
				
		sw $a0, 116($sp)		# moving up to p for our assignment
		li $a0, 1		# expression is TRUE
		lw $t0, 116($sp)		# loaded expression to prepare for assignment
		sw $a0, ($t0)		# assignment
				
		add $a0, $sp, 12		# id is a LOCAL SCALAR
				
		lw $a0, ($a0)		# fetch value for ID
		li $t0, 0		# begin of if statement
		beq $a0, $t0, _L33		# if they're both 0 we want to jump to else
		li $v0, 4		# printing a string
		la $a0, _L14		# printing the string by its label
		syscall		# system call for printing string
				
		j _L34		# end of positive part of if statement
_L33:				# begin negative part of if statement
		li $v0, 4		# printing a string
		la $a0, _L15		# printing the string by its label
		syscall		# system call for printing string
				
_L34:				# end of if statement
		li $v0, 4		# printing a string
		la $a0, _L16		# printing the string by its label
		syscall		# system call for printing string
				
				
		lw $ra, 4($sp)		# restore RA
		lw $sp, ($sp)		# restore SP
				
		li $v0, 10		# leave main program 
		syscall		# leave main 
