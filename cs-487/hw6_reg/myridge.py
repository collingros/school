# collin gros
# 04-02-2021
# cs-487
# hw6
#
#
# myridge.py
#
# this file contains the code for using Ridge with scikit-learn.
#
# NOTE: if things look weird, make your tabsize=8
#

from sklearn.linear_model import Ridge

# accuracy_score in score()
from sklearn.metrics import accuracy_score
# mean_squared_error() in mse()
from sklearn.metrics import mean_squared_error
# r2_score() in r2()
from sklearn.metrics import r2_score


# class skRidge
#
# this is the class used for performing Ridge on training/testing
# data.
#
# is initialized with training data and training labels
# with the constructor()
#
class skRidge:
	# model retrieved from scikit
	model = None

	# init()
	#
	# input: alpha
	# output: self.model is setup with given values
	#
	# initializes the model with given values
	#
	def __init__(self, alpha_):
		self.model = Ridge(alpha=alpha_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the model on the data provided
	#
	def fit(self, X_train, y_train):
		self.model.fit(X_train, y_train)


	# predict()
	#
	# input: the test data
	# output: the predicted labels
	#
	def predict(self, X_test):
		return self.model.predict(X_test)


	# score()
	#
	# input: the predicted labels, the targets
	# output: the accuracy (not %)
	#
	def score(self, y_pred, y_test):
		return accuracy_score(y_pred, y_test)


	# mse()
	#
	# input: labels, predicted labels
	# output: the mean squared error given the data
	#
	def mse(self, y, y_pred):
		return mean_squared_error(y, y_pred)


	# r2()
	#
	# input: labels, predicted labels
	# output: the value for R^2
	#
	def r2(self, y, y_pred):
		return r2_score(y, y_pred)








