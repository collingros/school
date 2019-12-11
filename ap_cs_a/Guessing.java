import java.util.Scanner;
import java.util.Random;

public class Guessing
{
  public static void main (String[] args)
  {
    final int MAX = 100;
    int answer, guess = 1, again = 1;
    Scanner scan = new Scanner (System.in);
    
    while (again == 1)
    {
      System.out.print ("I'm thinking of a number between 1 and " + MAX + ". Guess what it is: ");
      guess = scan.nextInt();
      
      Random generator = new Random();
      answer = generator.nextInt(MAX) + 1;
    
      while (guess != answer)
      {
        if (guess > answer)
        {
          System.out.println ("Your guess was too high. Try again: ");
          guess = scan.nextInt();
        }
        else
        {
          System.out.println ("Your guess was too low. Try again: ");
          guess = scan.nextInt();
        }
      }
      System.out.println ("Congratulations! You've won! The answer was " + answer);
      System.out.println ("Play again (1 for yes, any integer for no)?");
      again = scan.nextInt();
    }
    System.out.println ("Program Ended.");
  }
}