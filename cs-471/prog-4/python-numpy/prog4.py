# collin gros
# 09-28-2020
# cs471
# prog4 
#
#
# problem: print the time it takes to perform gauss elimination/substitution
# using python WITH numpy. can use pivoting.
#
# input: takes user input for matrix size
# output: time it takes to permform gauss elimination/subst.
#
# used https://numpy.org/doc/stable/reference/generated/numpy.linalg.solve.html
# as a reference
#
import time
import random
import numpy as np


# get matrix size
n = int(input("n: "))

# build the matrix out of random numbers (one for coefficients, the
# other for ordinary values)
coef_matrix = [[(random.random()*100) for i in range(n)] for j in range(n)]
ord_values = [(random.random()*100) for i in range(n)]

# start the clock
start = time.time()

# do gauss elimination + backwards substitution
sol_matrix = np.linalg.solve(coef_matrix, ord_values)

# stop the clock
stop = time.time()

print("time: " + str(stop-start))

