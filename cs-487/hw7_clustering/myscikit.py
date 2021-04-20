# collin gros
# 04-19-2021
# cs-487
# hw7
#
#
# myscikit.py
#
# this file contains the code for using agglomerativeclustering with
# scikit-learn.
#
# NOTE: if things look weird, make your tabsize=8
#

from sklearn.cluster import AgglomerativeClustering as AC

# accuracy_score in score()
from sklearn.metrics import accuracy_score


# class skAC
#
# this is the class used for performing AC on training/testing
# data.
#
# is initialized with training data and training labels
# with the constructor()
#
class skAC:
	# model retrieved from scikit
	model = None
	cluster_labels = None

	# init()
	#
	# input: n_clusters, affinity, linkage
	# output: self.model is setup with given values
	#
	# initializes the model with given values
	#
	def __init__(self, n_clusters_, affinity_, linkage_):
		self.model = AC(n_clusters=n_clusters_, affinity=affinity_,
				linkage=linkage_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the model on the data provided
	#
	def fit(self, X_train, y_train):
		self.cluster_labels = self.model.fit_predict(X_train, y_train)


	# predict()
	#
	# input: the test data (means nothing, just there for convention)
	# output: the predicted labels
	#
	def predict(self, X_test=None):
		return self.cluster_labels




	# score()
	#
	# input: the predicted labels, the targets
	# output: the accuracy (not %)
	#
	def score(self, y_pred, y_test):
		return accuracy_score(y_pred, y_test)









