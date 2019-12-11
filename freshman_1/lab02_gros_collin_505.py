#NAME
#Collin Gros

#COURSE
#Programming Principles - Lecture 003 Lab 005

#DATE
#9/12/2017

#PROBLEM
#Write a Python program that takes as input a month and year, determines how many days are in the month, and outputs the number of days.

#GIVEN
#Thirty days are in September, April, 
#June, and November.  All the rest are 31 except for February which could be 28 or 29 depending upon whether the year 
#is a leap year or not.  In general, a year is a leap year when it is evenly divisible by 4.  Exceptions occur when the year is 
#also evenly divisible by 100 in which case the year would not be a leap year unless it is evenly divisible by 400.

#ANALYSIS
#I need to store the number of days of each month into their own variables.
#I need to make multiple checks for situations that define a leap year.

#METHOD/ALGORITHM
#creating and storing known variables
#introduction
#input
#if checks for leap year
#match month with days & output

#PROGRAM
#creating and storing known variables
isLeapYear = False
#introduction
print("Welcome to the days in the month program.\n")
#input
month = input("Enter the month: ")
year = int(input("Enter the year: "))
#if checks for leap year
if(year % 400 == 0):
  isLeapYear = True
elif (year % 4 == 0) and (year % 100 != 0):
  isLeapYear = True
else:
  isLeapYear = False
#match month with days & output days and year
if (month == "January"):
  print(month, " ", year, " has 31 days.")
elif (month == "February" and isLeapYear):
  print(month, " ", year, " has 29 days.")
elif (month == "February" and not isLeapYear):
  print(month, " ", year, " has 28 days.")
elif (month == "March"):
  print(month, " ", year, " has 31 days.")
elif (month == "April"):
  print(month, " ", year, " has 30 days.")
elif (month == "May"):
  print(month, " ", year, " has 31 days.")
elif (month == "June"):
  print(month, " ", year, " has 30 days.")
elif (month == "July"):
  print(month, " ", year, " has 31 days.")
elif (month == "August"):
  print(month, " ", year, " has 31 days.")
elif (month == "September"):
  print(month, " ", year, " has 30 days.")
elif (month == "October"):
  print(month, " ", year, " has 31 days.")
elif (month == "November"):
  print(month, " ", year, " has 30 days.")
elif (month == "December"):
  print(month, " ", year, " has 31 days.")

