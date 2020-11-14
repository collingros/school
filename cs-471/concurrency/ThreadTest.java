/*
	collin gros
	11-11-2020
	cs471
	concurrency

	this class is used by the Concurrency class to assign threads a row
	and analyze it for statistics reported later in the Concurrency main()
	function.
*/

class ThreadTest implements Runnable
{
	int row;

	ThreadTest(int row)
	{
		// we are analyzing row #x
		this.row = row; 
	}


	public void run()
	{
		// initialize maximum to first element in row
		float max = Concurrency.A[row][0];
		// initialize minimum to first element in row
		float min = Concurrency.A[row][0];
		// initialize sum to 0
		float sum = 0;

		// analyze row #row
		// loop thu row; Concurrency.N = length/width of row
		for (int i = 0; i < Concurrency.N; ++i) {
			System.out.println("\t"+row+":\tA["+row+"]["+i+"]"
								+ ": " + Concurrency.A[row][i]);
			float val = Concurrency.A[row][i];
			// get min, max, sum
			if (max < val) {
				max = val;
			}
			if (min > val) {
				min = val;
			}

			sum += val;
		}
		// calculate avg with sum and N
		float avg = sum / Concurrency.N;


		// store values in an integer array, which is then stored
		// in the shared array Concurrency.stats
		float [] stats = {max, min, sum, avg};
		for (int i = 0; i < 4; ++i) {
			System.out.println(row+":\t stats["+i+"]: "+stats[i]);
		}

		try{
		Concurrency.stats[row] = stats;
		}
		catch (Exception e) {
			System.out.print(e);
			return;
		}
//		System.out.println(row+":\t max: "+max+" min: "+min+" sum: "+sum
//								+" avg: "+avg);
	}
}


