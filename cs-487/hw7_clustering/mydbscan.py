# collin gros
# 04-19-2021
# cs-487
# hw7
#
#
# mydbscan.py
#
# this file contains the code for using agglomerativeclustering with
# scikit-learn.
#
# NOTE: if things look weird, make your tabsize=8
#

from sklearn.cluster import DBSCAN

# accuracy_score in score()
from sklearn.metrics import accuracy_score


# class skDBSCAN
#
# this is the class used for performing DBSCAN on training/testing
# data.
#
# is initialized with training data and training labels
# with the constructor()
#
class skDBSCAN:
	# model retrieved from scikit
	model = None

	# init()
	#
	# input: eps, min_samples, metric
	# output: self.model is setup with given values
	#
	# initializes the model with given values
	#
	def __init__(self, eps_, min_samples_, metric_):
		self.model = DBSCAN(eps=eps_, min_samples=min_samples_,
					metric=metric_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the model on the data provided
	#
	def fit(self, X_train, y_train):
		self.labels = self.model.fit_predict(X_train, y_train)


	# predict()
	#
	# input: the test data
	# output: the predicted labels
	#
	def predict(self, X_test):
		return self.labels


	# score()
	#
	# input: the predicted labels, the targets
	# output: the accuracy (not %)
	#
	def score(self, y_pred, y_test):
		return accuracy_score(y_pred, y_test)









