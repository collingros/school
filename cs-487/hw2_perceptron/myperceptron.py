# collin gros
# 02-15-2021
# cs-487
# hw2
#
# myperceptron.py
#
# HEAVILY based off of the lecture notes from Tuan Le
# (CS-487 lecture notes (4))
#
# *********************************************
# NOTE: if viewing this looks off, change your
#	tabsize to 8
# *********************************************
#

import numpy as np


# this class implements the perceptron algorithm
class Perceptron:

	# eta (float): learning rate [0.0, 1.0]
	# n_iter (int): passes over the training
	#		dataset
	# random_state (int): random number generator
	#			seed for random weight
	#			initialization
	def __init__(self, eta=0.01, n_iter=50,
			random_state=1):
		# learning rate
		self.eta = eta
		# iterations
		self.n_iter = n_iter
		# seed for random weight
		self.random_state = random_state
		# weights
		self.w_ = None
		self.algo = "perceptron"


	def net_input(self, X):
		# return dot product between data(X) and weights
		return np.dot(X, self.w_[1:]) + self.w_[0]


	def predict(self, X):
		# decide between 1 and -1 if input is >=0
		return np.where(self.net_input(X) >= 0.0, 1, -1)


	# predict_and_correct()
	#
	# takes the data, and the answer, and does a prediction and
	# returns one if correct and zero if wrong.
	#
	# ** THRESHOLD HAS NO AFFECT HERE because this the prediction
	# is either 0 or 1
	#
	def predict_and_correct(self, X, y, threshold):
		output = self.predict(X)
		if y - output == 0:
			return 1
		return 0


	def fit(self, X, y):
		# init random generator
		rgen = np.random.RandomState(
				self.random_state)
		# init weights (from size of data)
		self.w_ = rgen.normal(loc=0.0,
				scale=0.01, size=1 +
				X.shape[1])
		# list to dump errors
		self.errors_ = []


		# CALCULATE WEIGHTS
		# do the specified number of iterations
		for _ in range(self.n_iter):
			errors = 0
			for xi, target in zip(X, y):
				# do the prediction with the goal to
				# adjust weights
				update = self.eta * (target - self.predict(xi))

				# updating all the weights with the adjustment
				# value
				self.w_[1:] += update * xi
				self.w_[0] += update

				# log errors
				errors += int(update != 0.0)
			self.errors_.append(errors)

		return self























