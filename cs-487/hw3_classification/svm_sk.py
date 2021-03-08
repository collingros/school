# collin gros
# 03-04-2021
# cs-487
# hw3
#
#
# svm_sk.py
#
# this code initializes the classifier SVM 
# from the scikit-learn classifier library.
#
# it can train and test on data from a dataset.
#
# NOTE: if things look weird, make your tabsize=8
#

# for the SVM nn
from sklearn.svm import SVC


# class skSVM 
#
# the class for the SVM algorithm fron
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skSVM:
	# the SVM object to use from scikit
	nn = None

	# init()
	#
	# input: kernel, C, random_state, gamma
	# output:
	#
	# initializes the SVM object
	#
	def __init__(self, kernel_='linear', C_=10.0, random_state_=1,
			gamma_=0.10):
		self.nn = SVC(kernel=kernel_, C=C_, random_state=random_state_,
				gamma=gamma_)


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








