import java.util.Scanner;

public class IntegerTest
{
  public static void main (String[] args)
  {
    int even = 0, odd = 0, zero = 0;
    Scanner scan = new Scanner (System.in);
    System.out.println ("Enter a number");
    String str = scan.nextLine();
    
    for (int read = 0; read <= str.length(); read++)
    {
      int x = str.charAt(read);
      if (x % 2 == 0)
        even += 1;
      else if (x % 2 != 0)
        odd += 1;
      else if (x == 0)
        zero += 1;
    }
    
    System.out.println ("Even digits: " + even);
    System.out.println ("Odd digits: " + odd);
    System.out.println ("Zeros: " + zero);
  }
}