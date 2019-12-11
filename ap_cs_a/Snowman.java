import java.applet.Applet;
import java.awt.*;

public class Snowman extends Applet
{
  public void paint (Graphics page)
  {
    final int MID = 150;
    final int TOP = 50;
    setBackground (Color.cyan);
    
    page.setColor (Color.black);
    page.fillRect (0, 555, 300, 50);
    
    page.setColor (Color.yellow);
    page.fillOval (-40, -40, 80, 80);
    
    page.setColor (Color.white);
    page.fillOval (MID-20, TOP, 40, 40);
    page.fillOval (MID-35, TOP+35, 70, 50);
    page.fillOval (MID-50, TOP+80, 100, 60);
    
    page.setColor (Color.black);
    page.fillOval (MID-10, TOP+10, 5, 5);
    page.fillOval (MID+5, TOP+10, 5, 5);
    
    page.drawArc (MID-10, TOP+20, 20, 10, 190, 160);
    
    page.drawLine (MID-25, TOP+60, MID-50, TOP+40);
    page.drawLine (MID+25, TOP+60, MID+55, TOP+60);
    
    page.drawLine (MID-20, TOP+5, MID+20, TOP+5);
    page.fillRect (MID-15, TOP-20, 30, 25);
  }
}