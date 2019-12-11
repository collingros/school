import java.text.DecimalFormat;
import java.util.Scanner;

public class Triangle
{
  public static void main (String[] args)
  {
    double a, b, c, s, h, f;
    
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter the three sides of the triangle: ");
    a = scan.nextDouble();
    b = scan.nextDouble();
    c = scan.nextDouble();
    
    s = a + b + c;
    h = (double) s / 2;
    f = Math.sqrt(s * (s - a) * (s - b) * (s - c));
    
    DecimalFormat fmt = new DecimalFormat ("0.###");
    
    System.out.println ("The area of the triangle is approximately: " + fmt.format(f));
  }
}