# collin gros
# 03-27-2021
# cs-487
# hw5_dim
#
#
# NOTE: if things look weird, make your tabsize=8

# arg handling
import sys
import argparse

# the implemented algorithms
import dec_tree_sk

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
	parser.add_argument('dimreduc', help='the dimreduc method to use. '
				'supported include pca, '
				'lda, kpca')
	parser.add_argument('dataset', help='the dataset to use. can be one '
				'of the presets, e.g., iris, digits, '
				'or mnist')

	# DT specific arguments
	parser.add_argument('-criterion', help='criterion, e.g., gini.')
	parser.add_argument('-max_depth', help='maximumd depth.', type=int)
	parser.add_argument('-random_state', help='random state.', type=int)

	# defaults
	parser.add_argument('-defaults', help='can be 1 or 0. 1 will make '
				'all required arguments their default vals.',
				type=int)
	
	args = parser.parse_args()

	if args.defaults == 1:
		# DT
		args.criterion = 'gini'
		args.max_depth = 4
		args.random_state = 1

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
	elif dataset == 'mnist':
		mnist = datasets.fetch_openml('mnist_784')
		X = mnist.data
		y = mnist.target
	else:
		print('ERROR: no dataset specified. you must specify a '
			'dataset!')
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
	X_train_std = sc.fit_transform(X_train)
	X_test_std = sc.transform(X_test)

	return X_train_std, X_test_std


# print_settings()
#
# input: arguments
# output: prints what arguments are passed to the classifier
#
def print_settings(args):
	if args.dimreduc == 'pca':
		print('criterion:\t{0}\nmax_depth:\t{1}\nrandom_state:\t{2}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state))
	else:
		print('cannot print settings for classifier \'{0}\', as it'
			' has not been implemented yet.\n'
			''.format(args.dimreduc))
		exit()


# get our command-line arguments.
args = get_args()
# extract data into X (data) and y (labels) from the given dataset
X, y = prepare_data(dataset=args.dataset)
# split newly aquired X and y into seperate datasets for training and testing
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3,
							random_state=1,
							stratify=y)
# perform feature scaling
X_train_std, X_test_std = do_feature_scaling(X_train, X_test)
# print settings
print_settings(args)


# start training/testing and use correct dimreduc
if args.dimreduc == 'pca':
	# load PCA
	pca_model = mypca.skPCA(args.







