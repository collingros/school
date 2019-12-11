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

import javax.swing.*;


class TestMonth
{
    public static void main(String[] args)
    {
        JFrame frame = new JFrame();
        Month month = new Month();

        int input;
        String tmp;

        do {
            tmp = JOptionPane.showInputDialog(frame, "MENU\n"
                                            + "[0]: Generate months\n"
                                            + "[1]: Sort generated months\n"
                                            + "[2]: Show generated months\n"
                                            + "[3]: Quit\n");
            input = Integer.parseInt(tmp);
            switch(input) {
                case 0:
                    month.generate_months();
                    break;
                case 1:
                    month.sort_months();
                    break;
                case 2:
                    month.show_months();
                    break;
            }
        }
        while (input != 3);
    }
}
