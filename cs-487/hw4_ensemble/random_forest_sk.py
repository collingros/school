# collin gros
# 03-08-2021
# cs-487
# hw4_ensemble
#
#
# random_forest_sk.py
#
# this code uses the sk RandomForestClassifier class
# to implement a rf ensemble algorithm, used
# by main.py to train and test on datasets.
#
# NOTE: if things look weird, make your tabsize=8
#

# RandomForestClassifier
from sklearn.ensemble import RandomForestClassifier as RFC


# class RFC
#
# the class for the RandomForestClassifier from
# scikit learn.
#
# is initialized with training data and training
# labels with the constructor()
#
class skRFC:
	# RF object
	forest = None


	# __init__()
	#
	# input:
	#
	def __init__(self, criterion_, n_estimators_, random_state_, n_jobs_):
		# initialize forest
		self.forest = RFC(criterion=criterion_,
					n_estimators=n_estimators_,
					random_state=random_state_,
					n_jobs=n_jobs_)


	# fit()
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the random forest classifier on the data provided
	#
	def fit(self, X_train, y_train):
		# train RFC
		self.forest.fit(X_train, y_train)


	# predict_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	# this function returns the accuracy of testing the RFC model
	# against the test data
	#
	def predict_score(self, X_test, y_test):
		return self.forest.score(X_test, y_test)










