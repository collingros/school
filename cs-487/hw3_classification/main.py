# collin gros
# 03-03-2021
# cs-487
# hw3_classification
#
# this file trains and tests several scikit-learn
# classifiers:
# (i) perceptron, (ii) support vector
# machine (linear, and non-linear using Radial
# Basis Function (RBF) kernel), (iii)
# decision tree, and (iv) K-nearest neighbor
#
# each is tested using two datasets, with the first
# being the digits dataset by scikit-learn, and the
# second being one containing time-series instances.
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
import dec_tree_sk
import k_nearest_sk
import perceptron_sk
import svm_sk

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
				'supported classifiers include knn, '
				'pcpn, svm, and dt')
	parser.add_argument('dataset', help='the dataset to use. can be one '
				'of the presets, e.g., iris, digits, '
				'or realistic_sensor_displacement, or can be '
				'a custom file. if it is a custom file, it '
				'must be '
				'in csv format, with data being on every '
				'column except the last, and labels being '
				'in the last column. other formats are not '
				'implemented yet.')
	# KNN specific arguments
	parser.add_argument('-neighbors', help='number of neighbors to use '
				'with KNN'
				'. must be an integer.', type=int)
	parser.add_argument('-p', help='p argument for scikit-learn KNN. must '
				'be an integer.', type=int)
	parser.add_argument('-metric', help='metric to use for scikit-learn '
				'KNN.')

	# perceptron specific arguments
	parser.add_argument('-epochs', help='epochs.', type=int)
	parser.add_argument('-eta', help='eta.', type=float)
	parser.add_argument('-random_state', help='random state.', type=int)

	# DT specific arguments
	parser.add_argument('-criterion', help='criterion, e.g., gini.')
	parser.add_argument('-max_depth', help='maximumd depth.', type=int)

	# SVM specific arguments
	parser.add_argument('-kernel', help='kernel. can be rbf or linear.')
	parser.add_argument('-cnum', help='c value for svm.', type=float)
	parser.add_argument('-gamma', help='gamma value for svm.', type=float)
	
	args = parser.parse_args()

	return args


# prepare_data()
#
# input:
#	filename of general dataset
#	(optional) specific dataset to use
#		can be 'iris'
#	*** NOTE: all data must be a CSV file ***
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

	elif dataset == 'realistic_sensor_displacement':
		df = pandas.read_csv('realistic_sensor_displacement/'
				'subject1_ideal.log', sep='\t')
		X = df.iloc[:, :-1]
		# select last column only for activity labels, and flatten
		# it
		y = df.iloc[:, -1:].values.ravel()

	# handle general dataset, specified in dataset
	else:
		print('specified dataset did not match pre-defined datasets.'
			' trying user-specified dataset...')
		try:
			df = pandas.read_csv(dataset)
			print('assuming data is everything on row except'
				' last column...')
			X = df.iloc[:, :-1]
			print('assuming labels are in the last column on '
				'every row...')
			y = df.iloc[:, -1:]
		except:
			print('ERROR: failed handling the dataset: \'{0}\''
				''.format(dataset))
			exit()


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


# test_all()
#
# trains and tests all algorithms and models. this is just for debugging
# purposes, really.
#
# input: training data, testing data, training data (feature scaled),
# 	 testing data (feature scaled), training labels, testing labels
# output: prints to the screen the accuracy of each algorithm on the dataset
#		(in percent)
#
def test_all(X_train, X_test, X_train_std, X_test_std, y_train, y_test):
	# *** PERCEPTRON ***
	print('...beg pnn...\n')
	begin_t = time.time()

	# load Perceptron
	ppn = perceptron_sk.skPerceptron()
	# train Perceptron
	ppn.fit(X_train_std, y_train)
	# predict using Perceptron
	print('prcp:\t\t{0:.2f}\n'
			''.format(ppn.predict_score(X_test_std,
							y_test)))
	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end pnn...\n')




	# *** KNN ***
	print('...beg knn...\n')
	begin_t = time.time()

	# load KNN
	knn = k_nearest_sk.skKNN()
	# train 
	knn.fit(X_train_std, y_train)
	# predict
	print('knn:\t\t{0:.2f}\n'
		''.format(knn.predict_score(X_test_std, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end knn...\n')


	# *** DT ***
	print('...beg dt...\n')
	begin_t = time.time()

	# load DT
	dt = dec_tree_sk.skDT()
	# train: DT does not require feature scaling.
	dt.fit(X_train, y_train)
	# predict: DT does not require feature scaling.
	print('dt:\t\t{0:.2f}\n'
			''.format(dt.predict_score(X_test, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end dt...\n')


	# *** SVM linear ***
	print('...beg svm-lin...\n')
	begin_t = time.time()

	# load SVM linear
	svm = svm_sk.skSVM(kernel_='linear', random_state_=1, C_=10.0)
	# train SVM 
	svm.fit(X_train_std, y_train)
	# predict using SVM
	print('svm-linear:\t{0:.2f}\n'
		''.format(svm.predict_score(X_test_std, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end svm-lin...\n')

	# *** SVM rbf ***
	print('...beg svm-rbf...\n')
	begin_t = time.time()

	# load SVM RBF
	svm = svm_sk.skSVM(kernel_='rbf', random_state_=1,
				gamma_=0.10, C_=10.0)
	# train SVM 
	svm.fit(X_train_std, y_train)
	# predict using SVM
	print('svm-rbf:\t{0:.2f}\n'
		''.format(svm.predict_score(X_test_std, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end svm-rbf...\n')







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

# train and test all models
#test_all(X_train, X_test, X_train_std, X_test_std, y_train, y_test)


# use the correct classifier based on args
if args.classifier == 'pcpn':
	# *** PERCEPTRON ***
	print('...beg pnn...\n')
	begin_t = time.time()


	# load Perceptron
	ppn = perceptron_sk.skPerceptron(epochs=args.epochs, eta=args.eta,
						rand_state=args.random_state)
	# train Perceptron
	ppn.fit(X_train_std, y_train)
	# predict using Perceptron
	print('pcpn:\t\t{0:.2f}\n'
			''.format(ppn.predict_score(X_test_std,
							y_test)))
	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end pnn...\n')
elif args.classifier == 'knn':
	# *** KNN ***
	print('...beg knn...\n')
	begin_t = time.time()

	# load KNN
	knn = k_nearest_sk.skKNN(n_neighbors_=args.neighbors, p_=args.p,
					metric_=args.metric)
	# train 
	knn.fit(X_train_std, y_train)
	# predict
	print('knn:\t\t{0:.2f}\n'
		''.format(knn.predict_score(X_test_std, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end knn...\n')
elif args.classifier == 'dt':
	# *** DT ***
	print('...beg dt...\n')
	begin_t = time.time()

	# load DT
	dt = dec_tree_sk.skDT(criterion_=args.criterion,
				max_depth_=args.max_depth,
				random_state_=args.random_state)
	# train: DT does not require feature scaling.
	dt.fit(X_train, y_train)
	# predict: DT does not require feature scaling.
	print('dt:\t\t{0:.2f}\n'
			''.format(dt.predict_score(X_test, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end dt...\n')
elif args.classifier == 'svm':
	# *** SVM ***
	print('...beg svm...\n')
	begin_t = time.time()

	# load SVM
	svm = svm_sk.skSVM(kernel_=args.kernel,
				random_state_=args.random_state,
				C_=args.cnum, gamma_=args.gamma)
	# train SVM 
	svm.fit(X_train_std, y_train)
	# predict using SVM
	print('svm:\t{0:.2f}\n'
		''.format(svm.predict_score(X_test_std, y_test)))

	end_t = time.time()
	elapsed = end_t - begin_t
	print('elapsed:\t{0}\n'.format(elapsed))
	print('...end svm...\n')
else:
	print('classifier \"{0}\" is not implemented! aborting...'
		''.format(args.classifier))
	exit()



