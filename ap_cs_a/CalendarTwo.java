import java.util.Scanner;

public class CalendarTwo
{
  public static void main (String[] args)
  {
    int year, yes, again;
    yes = 0;
    
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter a year: ");
    year = scan.nextInt();
    
    int remain = (year % 400);
    
    if (year % 4 == 0)
      year = yes;
    else
      System.out.println ("That is not a leap year.");
    
    if (year % 100 == 0)
      year = yes;
    else
      System.out.println ("That is not a leap year.");
    
    if (remain == 0)
      System.out.println ("That is not a leap year.");
    else
      System.out.println ();
    
    if (year == yes)
      System.out.println ("Yep, leap year.");
    else
      System.out.println ();
    
    System.out.println ("Try again? (Enter \"1\" if yes.");
    again = scan.nextInt();
    
    if (again == 1)
      S
  }
}