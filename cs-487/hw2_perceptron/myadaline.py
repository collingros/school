# collin gros
# 02-15-2021
# cs-487
# hw2
#
# myadaline.py
#
# HEAVILY based off of the lecture notes from Tuan Le
# (CS-487 lecture notes (5))
#
# *********************************************
# NOTE: if viewing this looks off, change your
#	tabsize to 8
# *********************************************
#

import numpy as np


# this class implements the adaline algorithm
class Adaline:

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
		self.algo = "adaline"


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
		if result < threshold:
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
		self.cost_ = []


		# do the specified number of iterations
		for _ in range(self.n_iter):
			output = self.net_input(X)
			errors = (y - output)
			# update weights and add cost
			self.w_[1:] += self.eta * X.T.dot(errors)
			self.w_[0] += self.eta * errors.sum()
			cost = (errors**2).sum() / 2.0
			self.cost_.append(cost)


		return self























