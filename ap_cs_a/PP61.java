import java.util.Scanner;

public class PP61
{
  public static void main (String[] args)
  {
    Scanner scan = new Scanner (System.in);
    int[] arr = new int [50];
    
    for (int index = 0; index < arr.length; index++) // Scans array and assigns numbers
    {
      int number = scan.nextInt();
      arr[index] = number;
    }
    
    for (int index = 0; index < arr.length; index++)
    {
      
      int currentNum = arr[index]; // assigns a number to the current number
      
      for (int index2 = 0; index < arr.length; index++)
      {
        if (arr[index] == currentNum) // checks to see if a number in the array equals the number in the previous for loop
        {
          int[] results = new int[50];
          
          for (int index3 = 0; index < results.length; index++)
          {
            int count = index3;
            results[count] = currentNum;
          }
        }
      }
    }
    
    for (int numbers = 0; numbers < arr.length; numbers++)
    {
      System.out.print (arr[numbers] + " ");
      System.out.print (results[numbers] + " ");
    }
  }
}