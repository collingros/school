/*
	collin gros
	11-11-2020
	cs471
	concurrency

	problem description: write a program in Java to create a square 2D matrix
							and calculate some basic statistics while
							measuring time.

*/
import java.util.ArrayList;
import java.util.Random;


class Concurrency
{
	private static ArrayList<Thread> arrThreads = new ArrayList<Thread>();

	// we use static variables to help us connect the threads
	// to a common block
	public static int N=0;
	public static int[][] A;

	public static void main(String[] args)
	{
		try {
			// take 1 input from the user (dimension of the square matrix [N])

			// create the array from input
			int size = Integer.parseInt(args[0]);
			// create 2D NxN INTEGER matrix
			A = new int[size][size];
	

			// randomly assign INTEGER values to each element
			

		// use only double/long
		// start timer

		// create N threads (each is responsible for one row of the matrix)

		// each thread calculates max, min, and stats for summation and avg
		// and stores them in shared set of arrays (global variable)

		// main thread waits on all of them to finish

		// calculate the overall max, min, and average

		// stop timer

		// use only int and float for max, sum, avg.
		// calculate the max value, min value, average of all values
		// in matrix,
		// the average of all of the values in the matrix, the time it
		// took to
		// do parts a-c
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}

