# collin gros
# 03-04-2021
# cs-487
# hw3
#
#
# perceptron_sk.py
#
# this code initializes the classifier Perceptron
# from the scikit-learn classifier library.
#
# it can train and test on data from a dataset.
#
# NOTE: if things look weird, make your tabsize=8
#

# for the Perceptron nn
from sklearn.linear_model import Perceptron
# for getting percentage accuracy from misclassifications
from sklearn.metrics import accuracy_score


# class skPerceptron
#
# the class for the Perceptron algorithm fron
# scikit learn.
#
# is initialized with training data and training labels
# with the constructor()
#
class skPerceptron:
	# the Perceptron object to use from scikit
	nn = None

	# init()
	#
	# input: epochs, eta (learning rate),
	#		rand_state (ensures reproduceability of initial
	#		shuffling of the training dataset after each epoch
	# output:
	#
	# initializes the Perceptron object
	#
	def __init__(self, epochs=40, eta=0.1, rand_state=1):
		self.nn = Perceptron(max_iter=epochs, eta0=eta,
					random_state=rand_state)
		print('eta: {0}'.format(eta))


	# fit()
	#
	# input: X_train (the data from dataset), y_train (the labels)
	# output:
	#
	# trains the nn on the data provided
	#
	def fit(self, X_train, y_train):
		self.nn.fit(X_train, y_train)


	# predict_test()
	#
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the predicted labels
	#
	def predict_test(self, X_test, y_test):
		y_pred = self.nn.predict(X_test)
		return y_pred


	# predict_score()
	# input: X_test (the testing data from the dataset),
	#		y_test (the testing labels from the dataset)
	# output: the accuracy of the predictions (in percents)
	#
	def predict_score(self, X_test, y_test):
		return self.nn.score(X_test, y_test)














