public class SortGrades
{
  public static void main (String[] args)
  {
    int[] grades = {89, 94, 69, 80, 97, 85, 73, 91, 77, 85, 93};
    
    Sorts.selectionSort (grades);
    
    for (int grade: grades)
      System.out.print (grades[grade] + " ");
  }
}