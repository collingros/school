public class Jump
{
  public static void main (String[] args)
  {
    try
    {
      String url = "https://akk.li/pics/anne.jpg";
      java.awt.Desktop.getDesktop().browse(java.net.URI.create(url));
    }
    catch (java.io.IOException e)
    {
      System.out.println(e.getMessage());
    }
  }
}