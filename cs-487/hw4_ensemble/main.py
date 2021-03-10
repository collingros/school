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
# additional sources (besides lecture):
#	# reading chronic kidney dataset
# 	https://mclguide.readthedocs.io/en/latest/sklearn/preprocessing.html
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

# for array manipulation
import numpy as np

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
				'or kidney.')
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


# print_settings()
#
# input: arguments
# output: prints what arguments are passed to the classifier
#
def print_settings(args):
	if args.classifier == 'bagging':
		print('criterion:\t{0}\nmax_depth:\t{1}\nrandom_state:\t{2}\n'
			'n_estimators:\t{3}\nn_jobs:\t{4}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state, args.n_estimators,
					args.n_jobs))
	elif args.classifier == 'random_forest':
		print('criterion:\t{0}\nrandom_state:\t{1}\n'
			'n_estimators:\t{2}\nn_jobs:\t{3}\n'
			''.format(args.criterion,
					args.random_state, args.n_estimators,
					args.n_jobs))
	elif args.classifier == 'adaboost':
		print('criterion:\t{0}\nmax_depth:\t{1}\nrandom_state:\t{2}\n'
			'n_estimators:\t{3}\nlearning_rate:\t{4}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state, args.n_estimators,
					args.learning_rate))
	else:
		print('cannot print settings for classifier \'{0}\', as it'
			' has not been implemented yet.\n'
			''.format(args.classifier))
		exit()


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
	elif dataset == 'kidney':
		fpath = 'Chronic_Kidney_Disease/chronic_kidney_disease.arff'
		header = [
				'age','bp','sg','al','su','rbc','pc','pcc',
				'ba','bgr','bu','sc','sod','pot','hemo','pcv',
				'wbcc','rbcc','htn','dm','cad','appet','pe',
				'ane','class'
				]
		kidney = pandas.read_csv(fpath, header=None, names=header,
						comment='@')
		# throw away '?'
		kidney.replace('?',  np.nan, inplace=True)
		kidney = kidney.dropna(axis=0, how='any')

		# replace all nominal values with 1 or -1
		kidney.replace('yes',  1, inplace=True)
		kidney.replace('no',  -1, inplace=True)
		kidney.replace('good',  1, inplace=True)
		kidney.replace('poor',  -1, inplace=True)
		kidney.replace('normal',  1, inplace=True)
		kidney.replace('abnormal',  -1, inplace=True)
		kidney.replace('present',  1, inplace=True)
		kidney.replace('notpresent',  -1, inplace=True)

		X = kidney.iloc[:, :-1]
		# flatten
		y = kidney.iloc[:, -1].values.ravel()

		# convert all nominal values to 1 or -1
		y = np.where(y == 'ckd', 1, -1)
	else:
		print('ERROR: this implementation does not allow custom'
			' datasets. please use one of the implemented ones,'
			' listed in \'python3 main.py -h\'  under'
			' datasets.')
		exit()
		

	return X, y



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
# print the settings used for the classifier
print_settings(args)

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
elif args.classifier == 'random_forest':
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
elif args.classifier == 'adaboost':
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



