// By Collin Gros
import java.util.Scanner;

public class Dealer
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("The Dealer is now running.");
    System.out.println ("How many cards would you like to be dealt?");
    int num = scan.nextInt();
    int count = 0;
    
    if (num <= 0)
      System.out.println ("Error: The number you entered is less than zero. Re-run the program to continue.");
    else
    {
      while (num != count)
      {
        count++;
        Card card = new Card();
        System.out.println ("Card " + count + " " + card);
      }
    }
    System.out.println ("Thank you for playing! (Program ended)");
  }
}