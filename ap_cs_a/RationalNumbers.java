import java.util.Scanner;

public class RationalNumbers
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    System.out.println ("Enter r1's numerator: ");
    int r1num = scan.nextInt();
    
    System.out.println ("Enter r1's denominator: ");
    int r1den = scan.nextInt();
    
    System.out.println ("Enter r2's numerator: ");
    int r2num = scan.nextInt();
    
    System.out.println ("Enter r2's denominator: ");
    int r2den = scan.nextInt();
    
    Rational r1 = new Rational (r1num, r1den);
    Rational r2 = new Rational (r2num, r2den);
    Rational r3, r4, r5, r6, r7;
    
    System.out.println ("First rational number: " + r1);
    System.out.println ("Second rational number: " + r2);
    if (r1.equals(r2))
      System.out.println ("r1 and r2 are equal.");
    else
      System.out.println ("r1 and r2 are NOT equal.");
    
    r3 = r1.reciprocal();
    System.out.println ("The reciprocal of r1 is: " + r3);
    
    r4 = r1.add(r2);
    r5 = r1.subtract(r2);
    r6 = r1.multiply(r2);
    r7 = r1.divide(r2);
    
    System.out.println ("r1 + r2: " + r4);
    System.out.println ("r1 - r2: " + r5);
    System.out.println ("r1 * r2: " + r6);
    System.out.println ("r1 / r2: " + r7);
  }
}