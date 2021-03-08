# collin gros
# 02-15-2021
# cs-487
# hw2
#
# mysgd.py
#
# HEAVILY based off of the lecture notes from Tuan Le
# (CS-487 lecture notes (6))
#
# *********************************************
# NOTE: if viewing this looks off, change your
#	tabsize to 8
# *********************************************
#

import numpy as np


# this class implements the sgd algorithm
class Sgd:

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
		self.algo = "sgd"


	def net_input(self, X):
		# return dot product between data(X) and weights
		return np.dot(X, self.w_[1:]) + self.w_[0]


	# randomly selects a range of values
	def _shuffle(self, X, y):
		# get a random selection of indicies and return them
		r = self.rgen.permutation(len(y))
		return X[r], y[r]


	# updates weights and returns cost
	def _update_weights(self, xi, target):
		output = self.net_input(xi)
		error = (target - output)

		self.w_[1:] += self.eta * xi.dot(error)
		self.w_[0] += self.eta * error
		cost = 0.5 * error**2

		return cost


	# predict_and_correct()
	#
	# takes the data, the answer, and does a prediction and
	# returns one if correct and zero if wrong.
	#
	# threshold is the leniency of the correct answer. for allowing more
	# innaccuracy, increase this threshold, and to constrict innaccuracy,
	# lower this number (to zero)
	#
	def predict_and_correct(self, X, y, threshold):
		output = self.net_input(X)
		result = y - output
		# result can be very close to zero, but not zero,
		# so i use a range here to consider what is a correct
		# guess
		if result < (0 + threshold) and result > (0 - threshold):
			return 1
		return 0


	def fit(self, X, y):
		# init random generator
		self.rgen = np.random.RandomState(
				self.random_state)
		# init weights (from size of data)
		self.w_ = self.rgen.normal(loc=0.0,
				scale=0.01, size=1 +
				X.shape[1])
		self.cost_ = []


		# do the specified number of iterations
		for _ in range(self.n_iter):
			X,y = self._shuffle(X, y)
			cost = []
			# start
			for xi, target in zip(X, y):
				cost.append(self._update_weights(xi, target))

			# save average cost for this iteration
			avg_cost = sum(cost) / len(y)
			self.cost_.append(avg_cost)


		return self























