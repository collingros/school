/*
	collin gros
	11-11-2020
	cs471
	concurrency

	problem description: write a program in Java to create a square 2D matrix
							and calculate some basic statistics while
							measuring time.

	this program calculates the max, min, sum, and avg of random int values
	stored in a square matrix of a given size, and prints the time
	it takes to do so (in nanoseconds).

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
	// each entry is an array in the following format:
	// 	max, min, sum
	public static float[][] stats;


	public static void main(String[] args)
	{
		try {
			// take 1 input from the user:
			// 	(dimension of the square matrix [N])

			// create the array from input
			N = Integer.parseInt(args[0]);
			// create 2D NxN INTEGER matrix
			A = new int[N][N];
			// create stats matrix (N x 3)
			stats = new float[N][3];
	

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
		// and stores them in shared set of arrays (stats[][])
		// and main thread waits on all of them to finish
		for (int i = 0; i < N; ++i) {
			// WAITING... join to NULL when thread is done
			arrThreads.get(i).join();
		}


		// calculate the overall max, min, and average
		// (recall that) each entry is an integer array in
		// the following format:
		// 	max, min, sum
		// initialize maximum to first max in matrix
		float max = Concurrency.A[0][0];
		// initialize minimum to first min in matrix
		float min = Concurrency.A[0][1];
		// initialize sum, avgs to 0
		float sum = 0, avgs = 0;
		for (int i = 0; i < N; ++i) {
			if (max < stats[i][0]) {
				max = stats[i][0];
			}
			if (min > stats[i][1]) {
				min = stats[i][1];
			}
			sum += stats[i][2];
			avgs += stats[i][3];
		}
		// calculate overall avg
		float avg = avgs / N;

		// save final results in array
		float[] totalstats = {max, min, sum, avg};

		// stop timer
		long stopTime = System.nanoTime();
		long duration = stopTime - startTime;


		// print final results
		System.out.println("total time(ns): " + duration);
		System.out.println("totalstats: max: "+totalstats[0]+" min: "
							+totalstats[1]+" sum: "+totalstats[2]
							+" avg: "+totalstats[3]);
		}
		catch (Exception e) {
			System.out.println(e.getMessage());
		}
	}
}

