# Collin Gros
# CS 1411 Programming Principles
# 09/19/2017

# Problem: 
# Allow the user to enter two integers to multiply and whether they want to continue multiplying integers.

# Given:
# If A and B are two integers to be multiplied, we repeatedly multiply A by 2 and divide B by 2 until B becomes zero. To figure out
# the product of A and B, we keep a running total where we add A every time the result of dividing B by 2 is an odd number.

# Analysis:
# Check if A and B are two integers, if they are, multiply A by 2 and divide B by 2 until B is zero. Keep track of the product.

# Method / Algorithm:
# introduction
# define functions for checking numbers and algorithm
# begin loop 
# take in values every time the loop starts
# call function for integers
# call algorithm function
# check if user wants to do it again and set while value to false if not





# introduction
print("Welcome to the Egyptian Algorithm Program!")

#defining functions
def integer_gatherer ():
    integer_string_1_done = False
    integer_string_2_done = False
    finished = False
    while not finished:
        if not integer_string_1_done: #if integer 1 does not exist yet
            integer_string_1 = input("Enter integer A: ")
            # for inputs that start with + or -
            if (integer_string_1[0] == '+' or integer_string_1[0] == '-') and integer_string_1[1:].isdigit(): #isdigit checks if numbers from [x:] to end of str are 0-9
                converted_integer_1 = int(integer_string_1)
                integer_string_1_done = True
            # for normal integers
            elif integer_string_1.isdigit():
                converted_integer_1 = int(integer_string_1)
                integer_string_1_done = True
            # if the input failed the integer tests
            else:
                print(integer_string_1, " is not an integer...")
        elif not integer_string_2_done: #if integer 2 does not exist yet
            integer_string_2 = input("Enter integer B: ")
            # for inputs that start with + or -
            if (integer_string_2[0] == '+' or integer_string_2[0] == '-') and integer_string_2[1:].isdigit(): #isdigit checks if numbers from [x:] to end of str are 0-9
                converted_integer_2 = int(integer_string_2)
                integer_string_2_done = True
            # for normal integers
            elif integer_string_2.isdigit():
                converted_integer_2 = int(integer_string_2)
                integer_string_2_done = True
            # if the input failed the integer tests
            else:
                print(integer_string_2, " is not an integer...")      
        else:
            finished = True
    #print("converted 1: ",converted_integer_1, " converted 2: ", converted_integer_2)
    return (converted_integer_1, converted_integer_2) # returns a and b

def algorithm(integer_a, integer_b):
    product = 0
    while integer_b > 0:
        if integer_b % 2 != 0: # if b is odd
            #print("product ", product)
            product += integer_a
        #print("integer_a ", integer_a)
        integer_a *= 2
        #print("integer_b", integer_b)
        integer_b //= 2 # integer division so it rounds down for the algorithm to work...
        
    return product
   
# Beginning of main program
done = False
user_response = 'y'
while not done:
    if user_response == 'y': # check if user wants to repeat
        a, b = integer_gatherer()
        final_result = algorithm(a, b) #perform algorithm and put it in final_result
        
        print(final_result, " is the product of the two integers you entered.")
        user_response = input("Do you want to multiply numbers again? (y or n): ")
    else: # exit statement
        done = True
    