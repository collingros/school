# collin gros
# 03-04-2021
# cs-487
# hw3
#
#
# k_nearest_sk.py
#
# this code initializes the classifier KNN
# from the scikit-learn classifier library.
#
# it can train and test on data from a dataset.
#
# NOTE: if things look weird, make your tabsize=8
#

# for the KNN nn
from sklearn.neighbors import KNeighborsClassifier as KNC


# class skKNN 
#
# the class for the KNN algorithm fron
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skKNN:
	# the KNN object to use from scikit
	nn = None

	# init()
	#
	# input: n_neighbors, p, metric.
	# output:
	#
	# initializes the KNN object
	#
	def __init__(self, n_neighbors_=5, p_=2, metric_='minkowski'):
		self.nn = KNC(n_neighbors=n_neighbors_, p=p_, metric=metric_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the nn on the data provided
	#
	def fit(self, X_train, y_train):
		self.nn.fit(X_train, y_train)


	# predict_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	def predict_score(self, X_test, y_test):
		return self.nn.score(X_test, y_test)








