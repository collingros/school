// Collin Gros Period 2 Oct 28, 2015 - pg 175 #3.1
import java.text.DecimalFormat;
import java.util.Scanner;

public class AverageRevised
{
  public static void main (String[] args)
  {
    int sum = 0, value, count = 0;
    double average;
    Scanner scan = new Scanner (System.in);
    
    System.out.print ("Enter an integer (0 to quit); ");
    value = scan.nextInt();
    
    while (value != 0)
    {
      count++;
      
      sum += value;
      System.out.println ("The sum so far is " + sum);
      
      System.out.print ("Enter an integer (0 to quit); ");
      value = scan.nextInt();
    }
    System.out.println();
    System.out.println ("Number of values entered: " + count);
    
    if (value == 0)
      System.out.println ("Application ended: No average.");
    else
    {
      average = (double) sum / count;
      
      DecimalFormat fmt = new DecimalFormat ("0.###");
      System.out.println ("The average is " + fmt.format(average));
    }
  }
}