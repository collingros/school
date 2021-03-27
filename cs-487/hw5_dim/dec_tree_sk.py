# collin gros
# 03-27-2021
# cs-487
# hw5
#
#
# dec_tree_sk.py
#
# this code initializes the classifier DT
# from the scikit-learn classifier library.
#
# it can train and test on data from a dataset.
#
# NOTE: if things look weird, make your tabsize=8
#

# for the DT tree_model
from sklearn.tree import DecisionTreeClassifier as DTC


# class skDT 
#
# the class for the DT algorithm fron
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skDT:
	# the DT object to use from scikit
	tree_model = None

	# init()
	#
	# input: criterion, max_depth, and random_state
	# output:
	#
	# initializes the DT object
	#
	def __init__(self, criterion_='gini', max_depth_=4,
			random_state_=1):
		self.tree_model = DTC(criterion=criterion_, max_depth=max_depth_,
				random_state=random_state_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the tree_model on the data provided
	#
	# NOTE: need to use feature scaled sets!
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


	# predict()
	#
	# input: the test data
	# output: the predicted labels
	#
	def predict(self, X_test):
		return self.tree_model.predict(X_test)








