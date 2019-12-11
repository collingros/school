import java.util.Scanner;

public class TimeConv
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    
    int hours, minutes, seconds;
    
    System.out.println ("Enter the amount of hours: ");
    hours = scan.nextInt();
    
    System.out.println ("Enter the amount of minutes: ");
    minutes = scan.nextInt();
    
    System.out.println ("Enter the amount of seconds: ");
    seconds = scan.nextInt();
    
    final int HOURS_F = hours * 60 * 60;
    final int MINUTES_F = minutes * 60;
    final int TOTAL = HOURS_F + MINUTES_F + seconds;
    
    System.out.println ("The total amount of seconds from what you entered is: " + TOTAL);
  }
}