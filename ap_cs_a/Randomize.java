public class Randomize
{
  public static void main (String[] args)
  {
    for (int k = 1; k <= 100; k++)
    {
      int n1 = (int) (Math.random(10));
      int n2 = (int) (Math.random(10)) * 4;
      boolean bool = (n1 == n2);
      System.out.print (bool + " n1 = " + n1 + " n2 = " + n2 + " ");
      
    }
  }
}