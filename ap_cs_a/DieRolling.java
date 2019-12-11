// Collin Gros Period 2 Nov 20th
import java.util.Scanner;

public class DieRolling
{
  public static void main (String[] args)
  {
    int numSides, result;
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("How many sides do you want to have on the die?");
    numSides = scan.nextInt();
    
    Die die1 = new Die(numSides);
    result = die1.roll();
    
    System.out.println ("The result was: " + result);
  }
}