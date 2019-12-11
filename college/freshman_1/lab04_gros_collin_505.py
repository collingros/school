#Collin Gros
#CS 1411 - Lab 005
#09/26/2017

#Problem:
#Encrypt and Decrypt sentences that are input .

#Given 
#Seperate the message into two groups of characters, the first group composed of the even-numbered characters and the second group composed of the odd-numbered characters. Put together both groups, placing the even numbered group first, followed by the odd numbered characters.

#Analysis
#I need to split the string, order it into different variables based on even or odd element numbers, combine the string variables and print them. Then, i need to do the opposite and print the decrypted string.

#Method / Algorithm
#Introduction
#Loop
#Input
#Encrypt --
#Order all even numbered elements into a string
#Order all odd numbered characters into a string
#Combine both groups, even first.
#Print
#Decrypt --
#Divide the string evenly
#Gather first half and call it even numbers
#Gather second half and call it odd numbers
#Print each value
#Ask if the user wants to restart

#Test Cases
#"I have a new puppy" -> " aeanwppylhv e up."
#" " -> " "
#"abc" -> "bac"

#Program
#Introduction
print("Welcome to the ciphyer text program!")
while True:
  #Input
  unconverted_string = input("Please enter a string for encryption: ")
  
  #Encrypt
  #Ordering Odds
  odd_string = unconverted_string[::2]
  #Ordering Evens
  even_string = unconverted_string[1: :2]
  #Combining Groups
  encryption = even_string + odd_string
  #Printing end result
  print("The encrypted string is: ", encryption)
  
  #Decrypt
  length = len(encryption)
  half = length // 2
  #print("half :", half)
  #Getting Evens
  d_even_string = encryption[:half]
  #Getting Odds
  d_odd_string = encryption[half:]
  #Decoding by printing each value (I tried extremely hard not to use lists)
  print("The decrypted string is: ")
  #using try/except so that the for loop does not surpass the length of a string in case it is an odd-numbered string
  try:
    for i in range(0, len(d_odd_string)):
      print(d_odd_string[i])
      print(d_even_string[i])
  except IndexError:
    break

  #Asking if the loop should continue
  response = input("Again? (y/n)")
  if response == "n":
    break
  
#Failed Attempts
 #if (len(decryption_combination) % 2 != 0):
  #  print(d_odd_string[::-2]
          
  #print(d_odd_string[0], d_even_string[0], d_odd_string[1], d_even_string[1])
  #if len(d_odd_string) < len(d_even_string):
  # min_str = d_odd_string
  #else:
  #  min_str = d_even_string 
  #if len(d_odd_string) > len(d_even_string):
  #  print(d_even_string[len(d_odd_string) - 1])
  #else:
  #  print(d_odd_string[len(d_even_string) - 1])




