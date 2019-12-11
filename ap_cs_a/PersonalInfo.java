import java.util.Scanner;
import java.math.*;

public class BMI
{
 public static void main (String[] args)
 {
  // declare variables
  int age, weight, height;
  
  Scanner scan = new Scanner (System.in);
  
  System.out.println ("Enter your age below (integer/years): ");
  age = scan.nextInt();
  // age is now typed in by user
  
  System.out.println ("Enter your weight below (integer/lbs): ");
  weight = scan.nextInt();
  // weight is now typed in by user
  
  System.out.println ("Enter your height below (integer/inches): ");
  height = scan.nextInt();
  // height is now typed in by user
  
  double weight_conv = weight * 0.45;
  double height_conv = height * 0.025;
  double height_final_conv = Math.pow( height_conv, 2);
  final double BMI = weight_conv / height_final_conv;
  
  System.out.println ("Your BMI is " + BMI + ". A healthy BMI ranges from 19 and 25.");
 }
}