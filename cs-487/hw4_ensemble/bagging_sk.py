# collin gros
# 03-08-2021
# cs-487
# hw4_ensemble
#
#
# bagging_sk.py
#
# this code uses the sk BaggingClassifier class
# to implement a bagging ensemble algorithm, used
# by main.py to train and test on datasets.
#
# NOTE: if things look weird, make your tabsize=8
#

# BaggingClassifier
from sklearn.ensemble import BaggingClassifier as BC
# DecisionTreeClassifier
from sklearn.tree import DecisionTreeClassifier as DTC


# class skBagging
#
# the class for the BaggingClassifier from
# scikit learn.
#
# is initialized with training data and training
# labels with the constructor()
#
class skBagging:
	# DT object to use
	tree = None
	# BaggingClassifier object
	bag = None


	# __init__()
	#
	# input:
	#
	def __init__(self, criterion_, max_depth_, random_state_,
			n_estimators_):
		# initialize DTC
		self.tree = DTC(criterion=criterion_, max_depth=max_depth_,
				random_state=random_state_)

		# initialize BaggingClassifier, with
		# n_estimators being the only adjustable value
		self.bag = BC(base_estimator=self.tree,
				n_estimators=n_estimators_, max_samples=1.0,
				max_features=1.0, bootstrap=True,
				bootstrap_features=False, n_jobs=1,
				random_state=1)


	# fit()
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the DTC tree and BaggingClassifier on the data provided
	#
	def fit(self, X_train, y_train):
		# train DTC tree
		self.tree.fit(X_train, y_train)
		# train BC
		self.bag.fit(X_train, y_train)


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


	# predict_bag_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	# this function returns the accuracy of testing the bagging model
	# against the test data
	#
	def predict_bag_score(self, X_test, y_test):
		return self.bag.score(X_test, y_test)























