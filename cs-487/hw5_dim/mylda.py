# collin gros
# 03-27-2021
# cs-487
# hw5
#
#
# mylda.py
#
# this file contains the code for the LDA dimension reduction technique.
#
# NOTE: if things look weird, make your tabsize=8
#

# LDA
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
# my decision tree wrapper
import dec_tree_sk

# accuracy_score in score()
from sklearn.metrics import accuracy_score


# class skLDA
#
# the class for the LDA dimreduc from
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skLDA:
	# the LDA object to use from scikit
	model = None
	# the DT object to use
	tree_model = None

	# init()
	#
	# input: criterion, max_depth, and random_state
	# output:
	#
	# initializes the DT object
	#
	def __init__(self, criterion_='gini', max_depth_=4,
			random_state_=1, n_components_=2):
		self.model = LDA(n_components=n_components_)
		self.tree_model = dec_tree_sk.skDT(criterion_, max_depth_,
							random_state_)


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the tree_model on the data provided
	#
	def fit(self, X_train, y_train):
		# get transformed train data
		X_train_lda = self.model.fit_transform(X_train, y_train)
		# use it to train DT
		self.tree_model.fit(X_train_lda, y_train)


	# predict()
	#
	# input: the lda test data
	# output: the predicted labels
	#
	def predict(self, X_test_lda):
		return self.tree_model.predict(X_test_lda)


	# score()
	#
	# input: the predicted labels, the targets
	# output: the accuracy (not %)
	#
	def score(self, y_pred, y_test):
		return accuracy_score(y_pred, y_test)


	# predict_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	def predict_score(self, X_test, y_test):
		return self.model.score(X_test, y_test)


	# transform_test()
	#
	# input: X_test_std (the feature scaled version of test data)
	# output: X_test_lda (lda.transform of that data)
	#
	def transform_test(self, X_test_std):
		return self.model.transform(X_test_std)








