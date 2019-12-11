import java.util.Scanner;

public class Echo
{
  public static void main (String[] args)
  {
    String message;
    Scanner scan = new Scanner (System.in);
    
    System.out.println ("Enter a line of text: ");
    
    message = scan.nextLine();
    
    System.out.println ("You entered: \" " + message + "\" ");
  }
}