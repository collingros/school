# collin gros
# 03-08-2021
# cs-487
# hw4_ensemble
#
#
# adaboost_sk.py
#
# this code uses the sk AdaBoostClassifier class
# to implement an AdaBoost ensemble algorithm, used
# by main.py to train and test on datasets.
#
# NOTE: if things look weird, make your tabsize=8
#

# AdaBoostClassifier
from sklearn.ensemble import AdaBoostClassifier as ABC
# DecisionTreeClassifier
from sklearn.tree import DecisionTreeClassifier as DTC


# class skABC
#
# the class for the AdaBoostClassifier from
# scikit learn.
#
# is initialized with training data and training
# labels with the constructor()
#
class skABC:
	# DT object to use
	tree = None
	# AdaBoostClassifier object
	ada = None


	# __init__()
	#
	# input:
	#
	def __init__(self, criterion_, max_depth_, random_state_,
			n_estimators_, learning_rate_):
		# initialize DTC
		self.tree = DTC(criterion=criterion_, max_depth=max_depth_,
				random_state=random_state_)

		# initialize AdaBoostClassifier, with
		# n_estimators and learning_rate being adjustable
		self.ada = ABC(base_estimator=self.tree,
				n_estimators=n_estimators_,
				learning_rate=learning_rate_,
				random_state=random_state_)


	# fit()
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the DTC tree and AdaBoostClassifier on the data provided
	#
	def fit(self, X_train, y_train):
		# train DTC tree
		self.tree.fit(X_train, y_train)
		# train ABC
		self.ada.fit(X_train, y_train)


	# predict_tree_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	# this function returns the accuracy of testing the DT model
	# against the test data
	#
	def predict_tree_score(self, X_test, y_test):
		return self.tree.score(X_test, y_test)


	# predict_ada_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	# this function returns the accuracy of testing the ABC model
	# against the test data
	#
	def predict_ada_score(self, X_test, y_test):
		return self.ada.score(X_test, y_test)























