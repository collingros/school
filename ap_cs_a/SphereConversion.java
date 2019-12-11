import java.util.Scanner;
import java.math.*;

public class SphereConversion
{
  public static void main (String[] args)
  {
    double radius;
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter the radius: ");
    radius = scan.nextDouble();
    
    final double AREA = Math.PI * ((double) 4/3) * (Math.pow(radius, 3));
    final double SURFACE_AREA = 4 * Math.PI * (Math.pow(radius, 2));
    
    System.out.println ("Area: " + AREA);
    System.out.println ("Surface Area: " + SURFACE_AREA);
  }
}