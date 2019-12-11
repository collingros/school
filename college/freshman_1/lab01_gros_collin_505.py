#Name: Collin Gros
#Course: 1411-003
#Date: 09/05/2017

#PROBLEM: 
#Write a Python program that prompts for an integer number. Take that number, add 2, multiply by 3, subtract
#6, and divide by 3. Output the result of EACH calculuation. You should get the number with which you started.

#GIVEN: 
#Add 2, multiply by 3, subtract 6, and divide by 3

#ANALYSIS:
#Input: an integer
#Output: the same integer as was input

#METHOD/ALGORITHM:
#introduction
#prompt for an integer
#performs calculuation and stores it into another variable
#outputs the final variable

#PROGRAM:

#introduction
print("This is the program project for Lab 01. The purpose of this program"
      " is to take in an integer from the user, perform calculations with it, "
      "and print the final variable.")
#Prompt for an integer and store it into a variable
user_input = int(input("Please input an integer: "))
#Perform calculations on number and store into another variable
user_output = (((user_input + 2) * 3) - 6) // 3
#Print the final calculuation 
print("The final outcome: " + str(user_output))
#Give the user time to read it
finished = input("Press ENTER to exit.")
