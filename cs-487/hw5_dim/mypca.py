# collin gros
# 03-27-2021
# cs-487
# hw5
#
#
# mypca.py
#
# this file contains the code for the PCA dimension reduction technique.
#
# NOTE: if things look weird, make your tabsize=8
#

# PCA
from sklearn.decomposition import PCA
# my decision tree wrapper
import dec_tree_sk.py


# class skPCA
#
# the class for the PCA dimreduc from
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skPCA:
	# the PCA object to use from scikit
	model = None

	# init()
	#
	# input: criterion, max_depth, and random_state
	# output:
	#
	# initializes the DT object
	#
	def __init__(self, criterion_='gini', max_depth_=4,
			random_state_=1, n_components_=2):
		self.model = PCA(n_components_)
		self.dt = dec_tree_sk.DT(criterion_, max_depth_,
						random_state_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the tree_model on the data provided
	#
	def fit(self, X_train, y_train):
		self.tree_model.fit(X_train, y_train)


	# predict_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	def predict_score(self, X_test, y_test):
		return self.tree_model.score(X_test, y_test)








