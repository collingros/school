/*
	collin gros
	09-29-2020
	cs484
	project1

	prints the probability that a user is online given
		bandwidth of the link
		bandwith req of each user
		total number of users n
		probability that any particular user is idle at a given time
		target number of users x


	reference for answer to P9 in textbook:
		https://www.studykorner.org/computer-networking-a-top-down-approach-6th-edition-solutions-to-review-questions-and-problems/

	i used the equation for part B given in the above reference under
	problem 9. i changed the probability to be 1 - {given} because
	the given probability is for idle users, when we want it to
	be for active users.

	also, the coeff() function is iterative, as many recursive solns
	online were far too slow to compute the large numbers necessary.
*/

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>


/*	given the two values of binomial coefficient, evaluate it

	reference:
		https://stackoverflow.com/questions/45966883/code-for-finding-binomial-coefficient-in-iterative-form

	input: n, r where n and r are part of (n)
										  (r) of binomial coefficient
	output: the evaluated coefficient 	*/
unsigned long coeff(unsigned long n, unsigned long r)
{
	unsigned long ans = 1;
	for (int i = 0; i < r; i++) {
		ans = (ans * (n - i)) / (i + 1);
	}

	return ans;
}


int main(int argc, char **argv)
{
	// not enough arguments specified, exit
	if (argc != 6) {
		fprintf(stderr, "ERROR: not enough arguments given!\nusage: "
						"./run [bandwith of link] [bandwidth requirement "
						"of each user] [total number of users] [probability "
						"that any particular user is idle at a given time] "
						"[a target number of users]\n");
		return 1;
	}

	// parse args
	float band_link = std::stof(argv[1]);
	float band_requ = std::stof(argv[2]);
	int n_users = std::stoi(argv[3]);
	double idle_prob = std::stof(argv[4]);
	int t_users = std::stoi(argv[5]);

	// prob is online
	double nidle_prob = 1 - idle_prob;


	// perform summation of binomial distribution to get probability
	double sum = 0;
	for (int i = t_users + 1; i <= n_users; ++i) {
		// calculate sucess
		double succ = pow(nidle_prob, i);
		// calculate failure
		double fail = pow(idle_prob, n_users - i);
		// calculate binomial coefficient
		unsigned long bc = coeff(n_users, i);
		sum = sum + (bc * succ * fail);
		//printf("i: %d\tbc: %ld\tsucc: %f\tfail: %f\tsum: %f\n", i, bc,
													//succ, fail, sum);
	}
	printf("probability: %.2f\n", sum * 100);

	return 0;
}
