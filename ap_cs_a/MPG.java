import java.util.Scanner;

public class MPG
{
  public static void main (String[] args)
  {
    double gas, start, finish, mpg;
    // declaring variables as doubles
    Scanner scan = new Scanner (System.in);
    // instansiating scanner as a new object
    System.out.println ("Enter the amount of gas (gallons): ");
    gas = scan.nextDouble();
    // user types gas
    System.out.println ("Enter the odometer reading at the start of the trip: ");
    start = scan.nextDouble();
    //  user types odometer reading at the strt
    System.out.println ("Enter the odometer reading at the end of the trip: ");
    finish = scan.nextDouble();
    // user types odometer reading at the finish
    mpg = (double)((double) finish - start ) / gas;
    // formula for mpg
    System.out.println ("The MPG of your automobile is: " + mpg);
    // writes the mpg
    // end
  }
}