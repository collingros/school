# collin gros
# 02-03-2021
# cs482
# hw1-python
#
# this program accomplishes all of the tasks listed in the
# problem description document "HW1_Python.pdf".
#
# NOTE: you will need the Anaconda environment to be running
# 		in order to execute this program.
#
#


import pandas
import numpy as np
import matplotlib.pyplot as plt
import sys


# colors and shapes for use in scatter plots
COLORS_ARR = ['b', 'g', 'r', 'c', 'm', 'y', 'k', 'w']
MARKERS_ARR = ['.', 's', 'p', '*', '8', '+', 'x', 'D']


# HANDLE COMMAND LINE ARGUMENTS
if len(sys.argv) != 2:
	print("ERROR: incorrect number of arguments ({0})".format(len(sys.argv)))
	print("USAGE: python3 main.py [DATA_FILE]")
	exit()
DATA_FILE = sys.argv[1]


# (#1)
# read the iris dataset into DataFrame
df = pandas.read_csv(DATA_FILE)

# (#2)
# calculate and print the number of rows and columns that
# this dataset contains
nrows = df.shape[0]
ncols = df.shape[1]
print("number of rows: {0}".format(nrows))
print("number of cols: {0}".format(ncols))

# (#3)
# get all values of the last column and print the distinct values of the
# last column.
print("distinct values of last column: {0}"
		"".format(df[df.columns[ncols-1]].unique()))

# (#4)
# calculate the num of rows, the avg value of the first column, the
# max value of the second column, and the min value of the third column
# when the last column has value "Iris-setosa"
print("number of rows: {0}".format(nrows))
print("first column average: {0}"
		"".format(df[df.columns[0]].mean()))
print("second column max: {0}".format(df[df.columns[1]].max()))

# get a df with only rows that have "Iris-setosa" in the last column
setosa_df = df.loc[df[df.columns[ncols-1]] == "Iris-setosa"]
print("third column min (with fourth column == \"Iris-setosa\"): {0}"
		"".format(setosa_df[df.columns[2]].min()))


# (#5)
# draw a scatter plot with the data of the first column and the second column
# (y axis represents the second column and x axis rep the first) show the
# points in different colors and shapes when the last column's values
# are different.

# sort rows by last column
df.groupby(df.columns[ncols-1])

# get number of unique values in last column: used for determining
# if we need to switch the color and shape for color list
nuniq_last_col = df[df.columns[ncols-1]].nunique();


# split the data into three seperate ones for each value in last column
uniq_col_dfs = [i for _, i in df.groupby(df.columns[ncols-1])]
# create initial plot
ax1 = df.plot.scatter(df.columns[0],
						df.columns[1],
						c=COLORS_ARR[0],
						marker=MARKERS_ARR[0])
# draw subsequent plots over initial plot
i = 1
for d in uniq_col_dfs:
	tmp_ax = d.plot.scatter(d.columns[0],
							d.columns[1],
							c=COLORS_ARR[i],
							marker=MARKERS_ARR[i],
							ax=ax1)
	i = i + 1


print("\nfigure saved in ./out.png...")
plt.savefig("out.png")
















