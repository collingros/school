
# wghich reads in a number and prints it back put
#




.data
L1: .asciiz "Please enter value: "
L2: .asciiz "The number read was "
L3:  .asciiz "The square is "
NL:  .asciiz "\n"
.align 2
buffer: .space 8 # we need this to read in values an then we can store them
.text

main:   # we need 3 words to store the value, and then RA and SP

        subu $a0, $sp, 12 
        sw $sp, ($a0)
        sw $ra, 4($a0)  
        move $sp, $a0  # adjust the stack pointer

	#Prints the prompt2 string
	li $v0, 4
	la $a0, L1
	syscall 

	#reads one integer from user and saves in t0
	li $v0, 5
	#addu $t0, $sp, 8   #$t0 is the memory location for our variable
	syscall
	sw $v0 8($sp)
	
	# sprint it back out  string
	li $v0, 4
	la $a0, L2
	syscall 

        # print out the number
	li $v0, 1 
	#addu $t0, $sp, 8   #Address of x
	lw $a0,8($sp)     # value of x  
	syscall      
	li $v0, 4   #  these 3 lines do a new line
	la $a0, NL
	syscall   


      # now we show how to read into interact with buffer[0] aand buffer[1]
      
        la $t0, buffer
        li $a0, 2
        sw $a0, ($t0)  #  buffer[0] = 2
        li $a0, 5
        sw $a0 4($t0) #  buffer[1]=5
        
        # print them back out
            
	li $v0, 1 
	la $t0, buffer
	lw $a0, ($t0)     #  buffer[0] 
	syscall  
	li $v0, 4   #  these 3 lines do a new line
	la $a0, NL
	syscall   
	
	li $v0, 1 
	la $t0, buffer
	lw $a0, 4($t0)     #  buffer[1] 
	syscall   
        li $v0, 4   #  these 3 lines do a new line
	la $a0, NL
	syscall           
        
        
exitProgram:   
          #put back RA and SP
          lw $ra 4($sp)
          lw $sp ($sp)
	 li $v0, 10  # system call to
    	syscall         # terminate program


