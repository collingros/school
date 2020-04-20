# collin gros
# 04/20/2020

# reads input from the user and calculates the sum of squares up to
# the number specified, then prints then number


 .data
str: .asciiz "The sum from 0 ... "
str1: .asciiz " is \n"
L1: .asciiz "Please enter value: "
L2: .asciiz "The number read was "
L3:  .asciiz "The square is "
NL:  .asciiz "\n"
.align 0

 .text  # directive that we are in the code segment
main:
        subu $a0, $sp, 16 # We want 4 mem locations for main SP, RA, i , s
        sw $ra, 4($a0)  # we need to store the RA in the Activation record
        sw $sp, ($a0) # store SP
        move $sp, $a0  # adjust SP

        sw $0, 8($sp)  # store 0 into memory -- counting variable 
        sw $0, 12($sp)  # store 0 into memory -- accumulating 
        
        
       	#Prints the prompt string
	li $v0, 4
	la $a0, L1
	syscall 

	#reads one integer from user and saves in t0
	li $v0, 5
	#addu $t0, $sp, 8   #$t0 is the memory location for our variable
	syscall
	sw $v0 16($sp)
 
       
loop:
        lw $t6, 8($sp)  #   
        mul $t7, $t6, $t6  #  i * i
        lw $t8, 12($sp)   #  s
        addu $t9, $t8, $t7  #  s + i*i
        sw $t9, 12($sp)  #   s= s + i*i 
        lw $t6, 8($sp)   # i 
        addu $t0, $t6, 1  # i+1
        sw $t0, 8($sp)  #  i = i + 1
        
        lw $t1, 16($sp) # grab value we read in
        ble $t0, $t1, loop  #   keep doing it for 100 times
        nop   # 
        
        
        la $a0, str
        li $v0 4  #   print str
        syscall # 
        nop   # 
   
   	lw $a0, 16($sp)
   	li $v0 1 # print the number 
   	syscall
             
        la $a0, str1
        li $v0 4  #   print str1
        syscall # 
        nop   # 
        
        lw $a0, 12($sp)
        li $v0 1 #   Print the answer
        syscall
        
       
        lw $ra, 4($sp)
        lw $sp , ($sp)  # put backl Ra and SP
        
        li $v0, 10 
        syscall     #  exit for MAIN only
        

