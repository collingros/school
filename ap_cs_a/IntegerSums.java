// Collin Gros Period 2 Oct 28, 2015 - pg 175 #3.4
import java.util.Scanner;

public class IntegerSums
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    int count = 0, sum = 0, number = 0, value;
    
    System.out.println ("Enter a positive integer that is above 2.");
    value = scan.nextInt();
    
    if (value >= 2)
    {
      while (count < value)
      {
        count += 2;
        sum += count;
      }
      System.out.println ("The sum is " + sum);
    }
    else
      System.out.println ("You did not enter a positive integer that is greater than 2. Program ended.");
  }
}