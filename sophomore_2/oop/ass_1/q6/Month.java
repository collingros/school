/*
Collin Gros
R11522165

2/8/19
CS-2365-001 OOP
Group 27 (Collin & Alex)
*/

/*
Q6:
Write a menu driven program which using switch-case and do-while loop. Input option using JOpionPane. Write methods for each of the following task. Invoke these methods from cases of switch statement:

a) Using Random generator, generate unique month names in a random fashion and store them in a String array of size 12.

b) Display the array elements as a single String using JOptionPane.

c) Change the case of each array element and display the array again

d) Sort the array elements using Selection Sort and display the sorted elements of the array as a single String.

e) Exit the program
*/

import java.util.Random;
import javax.swing.*;
import java.util.Arrays;


class Month
{
    private String[] months = new String[12];
    private JFrame frame = new JFrame();
    private Random rand = new Random();


    public void sort_months()
    // sort months using selection sort
    {
        String tmp;
        int min;
        for (int i = 0; i < months.length - 1; i++) {
            min = i;

            for (int j = i + 1; j < months.length; j++) {
                if (months[j].compareTo(months[min]) < 0)
                    min = j;
                }

            tmp = months[i];
            months[i] = months[min];
            months[min] = tmp;
        }
    }


    public void show_months()
    // display month arr using JFrame
    {
        String month_str = Arrays.toString(months);
        JOptionPane.showMessageDialog(frame, month_str);
    }


    public void generate_months()
    // generates an array of random months
    {
        int i = 0, r = 0;
        int[] history = new int[12];
        String month;

        while (i < 12) {
            r = rand.nextInt(12) + 1;
            if (month_exists(r, history))
                continue;

            history[i] = r;
            month = get_month(r);
            months[i] = month;

            i++;
        }
    }


    public boolean month_exists(int r, int[] history)
    // true if month already exists in history
    {
        for (int i = 0; i < history.length; i++) {
            if (history[i] == r)
                return true;
        }

        return false;
    }


    public String get_month(int r)
    // return a month name based on given integer
    {
        switch (r) {
            case 1:
                return "Janurary";
            case 2:
                return "February";
            case 3:
                return "March";
            case 4:
                return "April";
            case 5:
                return "May";
            case 6:
                return "June";
            case 7:
                return "July";
            case 8:
                return "August";
            case 9:
                return "September";
            case 10:
                return "October";
            case 11:
                return "November";
            case 12:
                return "December";
        }

        return "";
    }
}
