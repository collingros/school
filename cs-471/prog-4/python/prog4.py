# collin gros
# 09-28-2020
# cs471
# prog4
#
# problem: print the time it takes to perform gauss elimination/substitution
# using python WITHOUT numpy. can't use pivoting.
#
# input: takes user input for matrix size
# output: time it takes to permform gauss elimination/subst.
#
#
# !!! gauss elimination and substitution codes retrieved from
# https://www.codesansar.com/numerical-methods/gauss-elimination-method-python-program.htm
#

import random
import time

# get matrix size
n = int(input("n: "))

# build the matrix out of random numbers
A = [[(random.random()*100) for i in range(n+1)] for j in range(n)]

# start the clock
start = time.time()

# perform gauss elimination
for i in range(n):
	for j in range(i + 1, n):
		ratio = A[j][i]/A[i][i]
		for k in range(n + 1):
			A[j][k] = A[j][k] - ratio * A[i][k]

# perform back substitution and store result in x
x = [0] * n
x[n-1] = A[n-1][n]/A[n-1][n-1]
for i in range(n - 2, -1, -1):
	x[i] = A[i][n]
	for j in range(i + 1, n):
		x[i] = x[i] - A[i][j] * x[j]

	x[i] = x[i] / A[i][i]

# stop the clock
stop = time.time()

print("time: " + str(stop-start))

