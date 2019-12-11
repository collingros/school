/*
Collin Gros
CS 1411
11/28/2017

Problem:
Given the weight of strawberries and the number of students, calculate how many strawberries each student would get 
if the farm takes a portion out of the weight.

Given:
1 strawberry weighs 1 ounce
1 pound is 16 ounces
Write 2 functions: straw() and enterint(), straw() does the math and enterint() gets the information and checks them for errors

Analysis:
Start with getting the info form the user using the enter int function. I need to do the math in the straw function and print the results

Method/Algorithm:
Straw(), Enterint(), main(). Introduction, getting information, calling straw, doing math, printing result

TEST CASES
3 STUDENTS 40 POUNDS
"Of 40, the students receive 20 pounds plus the owners are adding 1 strawberrie(s)
for a total of 107 strawberries"
2 Students 5 Pounds
"Of 5, the students receive 2 pounds plus a half pound for a total of 40 strawberrie(s)
each student receives 20 strawberries"

program
*/
#include <stdio.h>

//straw for doing the math
int straw(int students, int weight){
    float h = weight / 2.0;
    int numStraw = h * 16;
    if (weight % 2 != 0)
      numStraw += 8;
    if (numStraw % students != 0){
      float add = students - (numStraw % students);
      numStraw += add;
    }
    numStraw = numStraw / 3;
    float temp = weight / 2.0;
    float studentsReceiveWeight = weight - temp;
    printf("Out of %d, the farm gets %.1f pounds, the students get %.1f pounds and each student gets %.1d strawberries.", weight, temp, studentsReceiveWeight, numStraw);
    
    return 0;
}

//getting information from user
void enter_int(int low, int high){
    while (1)
    {
        printf("Enter the number of students: \n");
        int numStudents;
        scanf("%d", &numStudents);
        if (numStudents < low || numStudents > high)
            {
                printf("%d is not between %d and %d. Try again: \n", numStudents, low, high);
            }
        else
        {
            printf("Enter the weight of the strawberries picked (pounds): \n");
            int numStrawberries;
            scanf("%d", &numStrawberries);
            if (numStrawberries < low || numStrawberries > high)
            {
                printf("%d is not between %d and %d. Try again: \n", numStrawberries, low, high);
            }
            else
                straw(numStudents, numStrawberries);
                break;
        }
    }
}
// calling function
int main(){
  printf("Welcome to the pick your strawberry program. \n");
  enter_int(0, 5000);
  return 0;
}
