import java.util.Scanner;

public class Quadratic
{
  public static void main (String[] args)
  {
    int a, b, c;
    Scanner scan = new Scanner (System.in);
    
    System.out.print ("Enter the coefficient of x squared: ");
    a= scan.nextInt();
    
    System.out.print ("Enter the coefficient of x: ");
    b = scan.nextInt();
    
    System.out.print ("Enter the constant: ");
    c = scan.nextInt();
    
    double discriminant = Math.pow(b, 2) - (4 * a * c);
    double root1 = ((-1 * b) + Math.sqrt(discriminant)) / (2 * a);
    double root2 = ((-1 * b) - Math.sqrt(discriminant)) / (2 * a);
    
    System.out.println ("Root #1: " + root1);
    System.out.println ("Root #2: " + root2);
  }
}