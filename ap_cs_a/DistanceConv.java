import java.util.Scanner;

public class DistanceConv
{
  public static void main (String[] args)
  {
    double miles, kilometers;
    
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter the distance to convert to Kilometers (in miles): ");
    miles = scan.nextDouble();
    
    kilometers = miles * 1.60935;
    
    System.out.println (miles + " in Kilometers is: " + kilometers );
  }
}