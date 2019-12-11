import java.text.DecimalFormat;
import java.util.Scanner;

public class Coords
{
  public static void main (String[] args)
  {
    double x1, y1, x2, y2;
    
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter the X(1) Coordinate: ");
    x1 = scan.nextDouble();
    
    System.out.println ("Enter the Y(1) Coordinate: ");
    y1 = scan.nextDouble();
    
    System.out.println ("Enter the X(2) Coordinate: ");
    x2 = scan.nextDouble();
    
    System.out.println ("Enter the Y(2) Coordinate: ");
    y2 = scan.nextDouble();
    
    double first = x2 - x1;
    double second = y2 - y1;
    
    double first_f = Math.pow(first, 2);
    double second_f = Math.pow(second, 2);
    
    double before = first_f + second_f;
    
    double distance = Math.sqrt(before);
    
    DecimalFormat fmt = new DecimalFormat ("0.###");
    
    System.out.println ("The distance between the two points you entered is about: " + fmt.format(distance));
  }
}