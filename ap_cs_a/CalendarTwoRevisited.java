// Collin Gros Period 2 Oct 28, 2015 - pg 175 #3.2
import java.util.Scanner;

public class CalendarTwoRevisited
{
  public static void main (String[] args)
  {
    int year, yes;
    yes = 0;
    
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter a year (0 to quit): ");
    year = scan.nextInt();
    
    System.out.println ("Note: if one \"That is not a leap year.\" is displayed, the year is not a leap year.");
    
    int remain = (year % 400);
    
    while (year != 0)
    {
      
    if (year % 4 == 0)
      year = yes;
    else
    {
      System.out.println ("That is not a leap year.");
      year = 0;
    }
    
    if (year % 100 == 0)
      year = yes;
    else
    {
      System.out.println ("That is not a leap year.");
      year = 0;
    }
    
    if (remain == 0)
      System.out.println ("That is not a leap year.");
    else
    {
      System.out.println ();
      year = 0;
    }
    
    if (year == yes)
    {
      System.out.println ("That is a leap year if there wasn't a \"That is not a leap year.\" message!");
      year = 0;
    }
    else
      System.out.println ();
    }
    System.out.println ("The program is over.");
  }
}