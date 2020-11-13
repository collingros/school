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
import java.util.concurrent.TimeUnit;


class Concurrency
{
	// we use static variables to help us connect the threads
	// to a common block
	private static ArrayList<Thread> arrThreads = new ArrayList<Thread>();

	// N is the size of the NxN matrix of random numbers, and the
	// number of threads created
	public static int N = 0;

	// A stores random numbers to analyze
	public static int[][] A;

	// stats stores statistics for each row analyzed; written to by threads
	// each entry is an integer array in the following format:
	// 	max, min, sum, avg
	public static int[][] stats;


	public static void main(String[] args)
	{
		try {
			// take 1 input from the user:
			// 	(dimension of the square matrix [N])

			// create the array from input
			N = Integer.parseInt(args[0]);
			// create 2D NxN INTEGER matrix
			A = new int[N][N];
			// create stats matrix (N x 4)
			stats = new int[N][4];
	

			// randomly assign INTEGER values to each element
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					// in the range of  between 2^(32-N) and 2^(31-N)
					// trunc(  (2^(32-N) - (2^31-N))* Random()   + 2^(31-N))
					double tmp = Math.pow(2, 32-N)
									- Math.pow(2, 31-N);
					int x = (int) (Math.pow(2, 31-N)
								+ (Math.random() * tmp));
					A[i][j] = x;
				}
			}

		// use only double/long
		// start timer
		long startTime = System.nanoTime();

		// create N threads (each is responsible for one row of the matrix)
		for (int i = 0; i < N; ++i) {
			Thread t = new Thread(new ThreadTest(i));
			t.start();
			arrThreads.add(t);
		}

		// each thread calculates max, min, and stats for summation and avg
		// and stores them in shared set of arrays (global variable)

		// main thread waits on all of them to finish

		// calculate the overall max, min, and average

		// stop timer
		long stopTime = System.nanoTime();
		long duration = stopTime - startTime;

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

