# collin gros
# 02-15-2021
# cs-487
# hw2
#
# *********************************************
# NOTE: if viewing this looks off, change your
#	tabsize to 8
# *********************************************

# argument handling
import sys

# the implemented algorithms
import myperceptron
import myadaline
import mysgd

import pandas
import matplotlib.pyplot as plt
import numpy as np


# path to save graph
IMG_OUT = "out.png"


# init()
# handles command line arguments - gets DATA_FILE and ALGO from command
# line
#
# returns the arguments in a list
#	0: the algorithm to use (perceptron, adaline, sgd)
#	1: the file used for data
def init():
	args = []

	# HANDLE COMMAND LINE ARGUMENTS
	# wrong number of arguments?
	if len(sys.argv) != 3:
		print("len != 3!")
		print("ERROR: incorrect number of arguments ({0})"
			"".format(len(sys.argv)))
		print("USAGE: python3 main.py [[perceptron][adaline][sgd]] "
			"[DATA_FILE]\nNOTE: if you would like to use the "
			"iris dataset, make sure your file path includes "
			"the characters \"iris\" somewhere in it.")
		exit(1)

	# wrong argument names?
	algos = ["adaline", "sgd", "perceptron"]
	if (sys.argv[1] not in algos):
		print("ERROR: invalid argument name \"{0}\""
			"".format(sys.argv[1]))
		print("USAGE: python3 main.py [[perceptron][adaline][sgd]] "
			"[DATA_FILE]\nNOTE: if you would like to use the "
			"iris dataset, make sure your file path includes "
			"the characters \"iris\" somewhere in it.")
		exit(2)

	args.append(sys.argv[1])
	args.append(sys.argv[2])

	return args


# train_Algo()
#
# takes the algorithm name, X (data), y (key/labels), and
# eta and num interations.
# trains the data
#
# returns the trained model
#
def train_algo(algo, X, y, eta, itr):
	model = None

	# init correct model based on algorithm choice
	if algo == "perceptron":
		model = myperceptron.Perceptron(eta, itr)
	elif algo == "adaline":
		model = myadaline.Adaline(eta, itr)
	elif algo == "sgd":
		model = mysgd.Sgd(eta, itr)

	# train the data
	model.fit(X, y)

	return model


# graph()
#
# takes a trained model, and saves the graphs created from training.
#
# returns nothing
def graph(model):
	# draw appropriate graphs
	if model.algo == "perceptron":
		# draw graph
		plt.plot(range(1, len(model.errors_) + 1), model.errors_,
								marker='o')
		plt.xlabel("Epochs")
		plt.ylabel("Number of updates")
	elif model.algo == "adaline":
		# draw graph
		plt.plot(range(1, len(model.cost_) + 1), model.cost_,
								marker='o')
		plt.xlabel("Epochs")
		plt.ylabel("Cost")
	elif model.algo == "sgd":
		# draw graph
		plt.plot(range(1, len(model.cost_) + 1), model.cost_,
								marker='o')
		plt.xlabel("Epochs")
		plt.ylabel("Average Cost")

	print("saving plot as \"{0}\"".format(IMG_OUT))
	plt.savefig(IMG_OUT)


# rip()
#
# takes the path to the dataset file, the range of values to read,
# range_min is inclusive while range_max is exclusive
# and gets X and y from it.
#
# returns X (data) and y (labels)
def rip(dataset, range_min, range_max):
	# read the given dataset into a DataFrame (df)
	df = pandas.read_csv(dataset)

	X = None
	y = None
	# special selection in iris dataset: we want to compare setosa
	if "iris" in dataset:
		# "select setosa and versicolor" only from our dataset
		y = df.iloc[range_min:range_max, 4].values
		# "convert the class labels to two integer[s]" (answers)
		y = np.where(y == "Iris-setosa", -1, 1)
		# "extract sepal length and petal length" (data)
		X = df.iloc[range_min:range_max, [0, 2]].values

	return X, y


# test_algo()
#
# takes the model to test, along with the subset of data to test with
# and determines what the accuracy of the model is
#
# threshold is the leniency of the correct answer. for allowing more
# innaccuracy, increase this threshold, and to constrict innaccuracy,
# lower this number (to zero)
#
# returns nothing
#
def test_algo(model, X, y, threshold):
	correct = 0
	incorrect = 0
	for xi, target in zip(X, y):
		if(model.predict_and_correct(xi, target, threshold)):
			correct += 1
		else:
			incorrect += 1

	accuracy = (correct / (incorrect + correct))*100
	print("accuracy: {0}".format(accuracy))


# handle command line arguments
args = init()
# read TRAINING slice of dataset and get X (data) and y (labels) from it
# gets slice of set 0 through 49
train_X, train_y = rip(args[1], 0, 100)
# train chosen algorithm and get the model for it
model = train_algo(args[0], train_X, train_y, 0.0001, 10)

# read TESTING slice of dataset and get X (data) and y (labels) from it
#test_X, test_y = rip(args[1], 0, 100)
test_X = train_X
test_y = train_y
# test chosen algorithm, stores prediction statistics in model attributes
# gets slice of test data, also passes the threshold of what is considered
# a correct answer. the lower the last number the more strict the "grading"
test_algo(model, test_X, test_y, 1)

# draw graph of errors/cost of model
graph(model)






