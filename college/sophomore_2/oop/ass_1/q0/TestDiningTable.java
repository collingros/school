/*
Collin Gros
R11522165

2/8/19
CS-2365-001 OOP
Group 27 (Collin & Alex)
*/

/*
Q0:
Create a class DiningTable with attributes cost, weight, length and width. Provide methods that calculate the Table’s perimeter and area. It has set and get methods for weight, length and width. The set methods should verify that weight, length and width are all floating-point numbers larger than 0.0 and less than 20.0. Also provide the cost method which generates the cost of DiningTable in dollars using the formula:

cost = weight * length * width

Write a class TestDiningTable to test the class DiningTable. In the TestDiningTable class, use a ‘while’ loop to call each method of DiningTable class using input from keyboard (using Scanner class). If the values are not correct input again and show the results in a formatted manner using JOptionPane. Program stops if there is no more test data. Data encapsulation required.
*/

import java.util.Scanner;
import javax.swing.*;


class TestDiningTable
{
    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        DiningTable table = new DiningTable();
        float input, tmp;
        int stage = 0, err = 1;
        String tmp_str;

        while (stage < 4) {
            tmp = 0.0f;
            err = 1;

            if (stage == 0) {
                input = Float.parseFloat(JOptionPane.showInputDialog(frame, "enter a weight"));

                err = table.set_weight(input);
                if (err == -1) {
                    JOptionPane.showMessageDialog(frame, "entered input is invalid");
                    continue;
                }

                tmp = table.get_weight();
                tmp_str = String.format("weight is now: %f", tmp);

                JOptionPane.showMessageDialog(frame, tmp_str);

                stage++;
            }
            else if (stage == 1) {
                input = Float.parseFloat(JOptionPane.showInputDialog(frame, "enter a length"));

                err = table.set_length(input);
                if (err == -1) {
                    JOptionPane.showMessageDialog(frame, "entered input is invalid");
                    continue;
                }

                tmp = table.get_length();
                tmp_str = String.format("length is now: %f", tmp);

                JOptionPane.showMessageDialog(frame, tmp_str);

                stage++;
            }
            else if (stage == 2) {
                input = Float.parseFloat(JOptionPane.showInputDialog(frame, "enter a width"));

                err = table.set_width(input);
                if (err == -1) {
                    JOptionPane.showMessageDialog(frame, "entered input is invalid");
                    continue;
                }

                tmp = table.get_width();
                tmp_str = String.format("width is now: %f", tmp);

                JOptionPane.showMessageDialog(frame, tmp_str);

                stage++;
            }
            else if (stage == 3) {
                table.cost();

                tmp = table.get_cost();
                tmp_str = String.format("calculated cost: %f", tmp);

                JOptionPane.showMessageDialog(frame, tmp_str);

                stage++;
            }
        }
    }
}
