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

public class DiningTable
{
    private float cost, weight, length, width;


    public void cost()
    {
        cost = weight * length * width;
    }


    public float get_cost()
    {
        return cost;
    }


    public float get_weight()
    {
        return weight;
    }


    public float get_length()
    {
        return length;
    }


    public float get_width()
    {
        return width;
    }


    public int set_weight(float input)
    {
        if (input <= 0.0 || input >= 20.0)
            return -1;

        weight = input;

        return 0;
    }


    public int set_length(float input)
    {
        if (input <= 0.0 || input >= 20.0)
            return -1;

        length = input;

        return 0;
    }


    public int set_width(float input)
    {
        if (input <= 0.0 || input >= 20.0)
            return -1;

        width = input;

        return 0;
    }
}
