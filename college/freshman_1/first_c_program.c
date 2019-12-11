/*
Collin Gros
CS 1411
11/14/2017


Problem: Write a program that takes in values for milage and outputs calculated results.

Given: Calculate milage reimbursement for a salesperson at a rate of $0.35 a mile.

Analysis: I need to use scanf to take in values and store calculations in a variable

Method / Algorithm: Introduction, Initial Values, Calculations, Displaying results

Test Cases:
beginning odometer: 13505.2 ending odometer: 13810.6 Traveled 305.4 miles,  reimbursement is $106.89

Program
*/
#include <stdio.h>

int main(){
  printf("MILEAGE REINBURSEMENT CALCULATOR\n"); // Title
  
  printf("Enter beginning odometer reading: \n");
  float reading; // Assigning odometer readings to values
  scanf("%f", &reading);
  
  printf("Enter ending odometer reading: \n");
  float ending; // ""
  scanf("%f", &ending);
  
  float difference = ending - reading;
  printf("You traveled %0.1f miles. \n", difference); // printing the difference
  // in milage
  float rate = 0.35;
  float money = rate * difference; // calculations with money
  printf("At %0.2f per mile, your reimbursement is $%0.2f \n", rate, money); // displaying result
}
