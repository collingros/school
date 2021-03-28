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
import mypca
import mylda
import mykpca

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

	# PCA/LDA/KPCA
	parser.add_argument('-n_components', help='num components to use with '
							'PCA/LDA/KPCA',
						type=int)

	# test mode: changes the way output is displayed to be script-friendly
	parser.add_argument('-t', help='test mode: changes the way output '
					'is displayed to be script-friendly. '
					'0 is default, 1 to turn on',
				type=int)

	# defaults
	parser.add_argument('-defaults', help='can be 1 or 0. 1 will make '
				'all required arguments their default vals.',
				type=int)
	
	args = parser.parse_args()

	# set defaults if desired (usually for testing)
	if args.defaults == 1:
		# DT
		args.criterion = 'gini'
		args.max_depth = 4
		args.random_state = 1
		# PCA/LDA/KPCA
		args.n_components = 2

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
			'n_components:\t{3}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state, args.n_components))
	elif args.dimreduc == 'lda':
		print('criterion:\t{0}\nmax_depth:\t{1}\nrandom_state:\t{2}\n'
			'n_components:\t{3}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state, args.n_components))
	elif args.dimreduc == 'kpca':
		print('criterion:\t{0}\nmax_depth:\t{1}\nrandom_state:\t{2}\n'
			'n_components:\t{3}\n'
			''.format(args.criterion, args.max_depth,
					args.random_state, args.n_components))
	else:
		print('cannot print settings for classifier \'{0}\', as it'
			' has not been implemented yet.\n'
			''.format(args.dimreduc))


# store_results()
#
# input: the results dict to store results in, time it took to train,
# 	time it took to test, accuracy
# output: the times and accuracy are stored in the results dict
#
def store_results(results, train_t, test_t, acc):
	results['train_t'] = train_t
	results['test_t'] = test_t
	results['acc'] = acc


# get our command-line arguments.
args = get_args()
# extract data into X (data) and y (labels) from the given dataset
X, y = prepare_data(dataset=args.dataset)


# split newly aquired X and y into seperate datasets for training and testing
X_train = None
X_test = None
y_train = None
y_test = None
# if dataset is mnist, we want to make it smaller since it is so big
if args.dataset != 'mnist':
	X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3,
								random_state=1,
								stratify=y)
else:
	X_train, X_test, y_train, y_test = train_test_split(X, y,
							train_size=5000,
							test_size=10000,
							random_state=1,
							stratify=y)
	
# perform feature scaling
X_train_std, X_test_std = do_feature_scaling(X_train, X_test)

# if script mode isn't enabled, then print settings
if args.t != 1:
	# print settings
	print_settings(args)


# results dict contains accuracy, and time values
# for train time, test time, and accuracy
results = {
	'train_t':-1,
	'test_t':-1,
	'acc': -1
}
# start training/testing and use correct dimreduc
if args.dimreduc == 'pca':
	# load PCA
	pca_model = mypca.skPCA(criterion_=args.criterion,
				max_depth_=args.max_depth,
				random_state_=args.random_state,
				n_components_=args.n_components)

	# *** TRAIN ***
	begin_t = time.time()
	pca_model.fit(X_train_std, y_train)
	end_t = time.time()
	train_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('pca training time: {0:.2f}s'
			''.format(train_t))

	# *** TEST ***
	# transform test data
	X_test_pca = pca_model.transform_test(X_test_std)
	begin_t = time.time()
	# actually test and get result
	y_pred = pca_model.predict(X_test_pca)
	acc = 100 * pca_model.score(y_pred, y_test)
	end_t = time.time()
	test_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('pca:\t\t\t{0:.2f}%\t{1:.2f}s\n'
			''.format(acc, test_t))

	store_results(results, train_t, test_t, acc)
elif args.dimreduc == 'lda':
	# load LDA
	lda_model = mylda.skLDA(criterion_=args.criterion,
				max_depth_=args.max_depth,
				random_state_=args.random_state,
				n_components_=args.n_components)

	# *** TRAIN ***
	begin_t = time.time()
	lda_model.fit(X_train_std, y_train)
	end_t = time.time()
	train_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('lda training time: {0:.2f}s'
			''.format(train_t))

	# *** TEST ***
	# transform test data
	X_test_lda = lda_model.transform_test(X_test_std)
	begin_t = time.time()
	# actually test and get result
	y_pred = lda_model.predict(X_test_lda)
	acc = 100 * lda_model.score(y_pred, y_test)
	end_t = time.time()
	test_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('lda:\t\t\t{0:.2f}%\t{1:.2f}s\n'
			''.format(acc, test_t))

	store_results(results, train_t, test_t, acc)
if args.dimreduc == 'kpca':
	# load KPCA
	kpca_model = mykpca.skKPCA(criterion_=args.criterion,
				max_depth_=args.max_depth,
				random_state_=args.random_state,
				n_components_=args.n_components)

	# *** TRAIN ***
	begin_t = time.time()
	kpca_model.fit(X_train_std, y_train)
	end_t = time.time()
	train_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('kpca training time: {0:.2f}s'
			''.format(train_t))

	# *** TEST ***
	# transform test data
	X_test_kpca = kpca_model.transform_test(X_test_std)
	begin_t = time.time()
	# actually test and get result
	y_pred = kpca_model.predict(X_test_kpca)
	acc = 100 * kpca_model.score(y_pred, y_test)
	end_t = time.time()
	test_t = end_t - begin_t

	# print if script mode is off
	if args.t != 1:
		print('kpca:\t\t\t{0:.2f}%\t{1:.2f}s\n'
			''.format(acc, test_t))

	store_results(results, train_t, test_t, acc)


# print if script mode is on
if args.t == 1:
	# print results for script friendliness
	for key, value in results.items():
		print(value, end='\t')



