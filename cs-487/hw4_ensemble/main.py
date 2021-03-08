# collin gros
# 03-08-2021
# cs-487
# hw4_ensemble
#
# this file trains and tests several ensemble learning approaches:
# (i) random forest, (ii) bagging,
# (iii) adaboost
#
# you can specify which classifier to use and see their options by running
# this file with '-h'
#
# all possible test cases are used for thourough
# testing.
#
# NOTE: if things look weird, make your tabsize=8
#

# arg handling
import sys
import argparse

# the implemented algorithms
import bagging_sk
import random_forest_sk
import adaboost_sk

# pandas for data handling
import pandas

# using small datasets (iris)
from sklearn import datasets
# for splitting data into training and testing data
from sklearn.model_selection import train_test_split
# for feature scaling
from sklearn.preprocessing import StandardScaler

# for timing
import time


# return the arguments
def get_args():
	parser = argparse.ArgumentParser()
	parser.add_argument('classifier', help='the classifier to use. '
				'supported classifiers include bagging, '
				'random_forest, adaboost')
	parser.add_argument('dataset', help='the dataset to use. can be one '
				'of the presets, e.g., iris, digits, '
				'or chronickidneydisease.')
	# DT/Bagging specific arguments
	parser.add_argument('-random_state', help='random state.', type=int)
	parser.add_argument('-criterion', help='criterion, e.g., gini.')
	parser.add_argument('-n_estimators', help='num estimators.', type=int)
	parser.add_argument('-max_depth', help='maximumd depth.', type=int)

	# ABC specific args
	parser.add_argument('-learning_rate', help='learning rate.', type=float)

	# RFC specific args
	parser.add_argument('-n_jobs', help='number of jobs(prlell)', type=int)

	# defaults
	parser.add_argument('-defaults', help='can be 1 or 0. 1 will make '
				'all required arguments their default vals.',
				type=int)
	
	args = parser.parse_args()

	if args.defaults == 1:
		# DT/Bagging/RFC
		args.criterion = 'entropy'
		args.max_depth = 4
		args.random_state = 1
		args.n_estimators = 500

		# RFC
		args.n_jobs = 2

		# ADA
		args.learning_rate = 0.1

	return args


# prepare_data()
#
# input:
#	specific dataset to use
#		can be 'iris' for example
# output:
#	X, y tuple where X is data and y is the labels
#
def prepare_data(dataset=''):
	X = None
	y = None

	# handle specific datasets
	if dataset == 'iris':
		iris = datasets.load_iris()
		# only using petal length and
		# petal width features
		X = iris.data[:, [2, 3]]
		y = iris.target

	elif dataset == 'digits':
		digits = datasets.load_digits()
		# transform from 8x8 to feature vector of length 64
		X = digits.images.reshape((len(digits.images), -1))
		y = digits.target

	return X, y


# do_feature_scaling()
#
# preforms feature scaling on training/testing data and returns them
#
# input: training data, testing daya
# output: training data feature scaled, testing data feature scaled
#
def do_feature_scaling(X_train, X_test):
	# perform feature scaling on train and testing sets
	sc = StandardScaler()
	sc.fit(X_train)
	X_train_std = sc.transform(X_train)
	X_test_std = sc.transform(X_test)

	return X_train_std, X_test_std


# get our command-line arguments.
# can access them like so:
#	python3 main.py -k 5
# print(args.k) -> 5
args = get_args()


# extract data into X (data) and y (labels) from the given dataset
X, y = prepare_data(dataset=args.dataset)

# split newly aquired X and y into seperate datasets for training and testing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3,
							random_state=1,
							stratify=y)

# perform feature scaling
X_train_std, X_test_std = do_feature_scaling(X_train, X_test)


# use the correct classifier based on args
if args.classifier == 'bagging':
	# load DT/Bagging
	bag_model = bagging_sk.skBagging(args.criterion, args.max_depth,
						args.random_state,
						args.n_estimators,
						args.n_jobs)

	# *** TRAIN DT/BAGGING ***
	begin_t = time.time()
	# train, does NOT require feature scaling
	bag_model.fit(X_train, y_train)
	# report time to train
	end_t = time.time()
	elapsed = end_t - begin_t
	print('dt/bagging training time: {0:.2f}s'
		''.format(elapsed))


	# *** TEST DT ***
	begin_t = time.time()
	# predict and get accuracy from DT
	acc = 100 * bag_model.predict_tree_score(X_test, y_test)
	end_t = time.time()
	elapsed = end_t - begin_t
	print('dt:\t\t\t{0:.2f}%\t{1:.2f}s\n'
		''.format(acc, elapsed))


	# *** TEST BAGGING ***
	# predict and get accuracy from Bagging
	begin_t = time.time()
	acc = 100 * bag_model.predict_bag_score(X_test, y_test)
	end_t = time.time()
	elapsed = end_t - begin_t
	print('bagging:\t\t{0:.2f}%\t{1:.2f}s\n'
		''.format(acc, elapsed))
if args.classifier == 'random_forest':
	# load RFC
	rfc = random_forest_sk.skRFC(args.criterion, args.n_estimators,
						args.random_state,
						args.n_jobs)

	# *** TRAIN RFC ***
	begin_t = time.time()
	# train, does NOT require feature scaling
	rfc.fit(X_train, y_train)
	# report time to train
	end_t = time.time()
	elapsed = end_t - begin_t
	print('rfc training time: {0:.2f}s'
		''.format(elapsed))


	# *** TEST RFC ***
	begin_t = time.time()
	# predict and get accuracy from DT
	acc = 100 * rfc.predict_score(X_test, y_test)
	end_t = time.time()
	elapsed = end_t - begin_t
	print('rfc:\t\t\t{0:.2f}%\t{1:.2f}s\n'
		''.format(acc, elapsed))
if args.classifier == 'adaboost':
	# load DT/AdaBoost
	ada_model = adaboost_sk.skABC(args.criterion, args.max_depth,
					args.random_state, args.n_estimators,
					args.learning_rate)

	# *** TRAIN DT/BAGGING ***
	begin_t = time.time()
	# train, does NOT require feature scaling
	ada_model.fit(X_train, y_train)
	# report time to train
	end_t = time.time()
	elapsed = end_t - begin_t
	print('dt/ada training time: {0:.2f}s'
		''.format(elapsed))


	# *** TEST DT ***
	begin_t = time.time()
	# predict and get accuracy from DT
	acc = 100 * ada_model.predict_tree_score(X_test, y_test)
	end_t = time.time()
	elapsed = end_t - begin_t
	print('dt:\t\t\t{0:.2f}%\t{1:.2f}s\n'
		''.format(acc, elapsed))


	# *** TEST BAGGING ***
	# predict and get accuracy from Bagging
	begin_t = time.time()
	acc = 100 * ada_model.predict_ada_score(X_test, y_test)
	end_t = time.time()
	elapsed = end_t - begin_t
	print('ada:\t\t\t{0:.2f}%\t{1:.2f}s\n'
		''.format(acc, elapsed))
else:
	print('classifier \"{0}\" is not implemented! aborting...'
		''.format(args.classifier))
	exit()



