import java.util.Scanner;

public class ProgProj // 3.9
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    int verse;
    
    System.out.println ("Enter the verses to print (0 to quit):");
    verse = scan.nextInt();
    
    if (verse != 0)
    {
      for (int count = 100; count != 99 - verse; count--)
      {
        System.out.println (count + " bottles of beer on the wall");
        System.out.println (count + " bottles of beer");
        System.out.println ("If one of those bottles should happen to fall");
        System.out.println ((count - 1) + " bottles of beer on the wall");
      }
    }
    else
      System.out.println ("Program Over");
  }
}
      