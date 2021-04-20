# collin gros
# 04-19-2021
# cs-487
# hw7
#
#
# mykmeans.py
#
# this file contains the code for using kmeans. with scikit-learn.
#
# NOTE: if things look weird, make your tabsize=8
#

from sklearn.cluster import KMeans

# accuracy_score in score()
from sklearn.metrics import accuracy_score


# class skKMeans
#
# this is the class used for performing kMeans on training/testing
# data.
#
# is initialized with training data and training labels
# with the constructor()
#
class skKMeans:
	# model retrieved from scikit
	model = None

	# init()
	#
	# input: n_clusters, init (e.g., 'random'), n_init,
	#	max_iter, tol, random_state
	# output: self.model is setup with given values
	#
	# initializes the model with given values
	#
	def __init__(self, n_clusters_, init_, n_init_, max_iter_,
			tol_, random_state_):
		self.model = KMeans(n_clusters=n_clusters_, init=init_,
					n_init=n_init_, max_iter=max_iter_,
					tol=tol_, random_state=random_state_)


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


	# sse()
	#
	# input: 
	# output: the inertia (sum of squared distances to closest
	#	cluster center
	#
	def sse(self):
		return self.model.inertia_








