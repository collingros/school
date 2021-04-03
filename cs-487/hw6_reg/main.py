# collin gros
# 04-02-2021
# cs-487
# hw6
#
#
# NOTE: if things look weird, make your tabsize=8

# arg handling
import sys
import argparse

# the implemented algorithms
import mylinear
import myridge
import myransac
import mylasso

# for splitting data into training and testing data
from sklearn.model_selection import train_test_split
# for feature scaling
from sklearn.preprocessing import StandardScaler

# for timing
import time

# for handling dataset
import pandas
import numpy as np


# filepaths for datasets
HOUSE_CSV = './house/house.csv'
CALI_CSV = './cali/cali.csv'


# return the arguments
def get_args():
	parser = argparse.ArgumentParser()
	parser.add_argument('method', help='what to use. can be linear, '
				'ridge, ransac, or lasso')
	parser.add_argument('dataset', help='the dataset to use. can be house'
				' or cali')

	# RANSAC
	parser.add_argument('-random_state', help='random state.', type=int)
	parser.add_argument('-max_trials', help='max trials.', type=int)
	parser.add_argument('-min_samples', help='min samples.', type=int)
	parser.add_argument('-loss', help='loss.')
	parser.add_argument('-residual_threshold', help='residual threshold.',
				type=float)

	# Ridge/Lasso
	parser.add_argument('-alpha', help='alpha.', type=float)

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
		# RANSAC
		args.random_state = 1
		args.max_trials = 100
		args.min_samples = 50
		args.loss = 'absolute_loss'
		args.residual_threshold = 5.0

		# Ridge/Lasso
		args.alpha = 1.0

		# disable script-friendly output
		args.t = 0

	return args


# prepare_data()
#
# input: either 'house' or 'cali' -> specifies the dataset to use (House Sales
#		in King County, or California Renewable Production 2010-2018)
# output:
#	X, y tuple where X is data and y is the labels
#
def prepare_data(dataset=''):
	X = None
	y = None

	# handle specific datasets
	if dataset == 'house':
		df = pandas.read_csv(HOUSE_CSV)
		# convert dates to integers
		df['date'] = pandas.to_datetime(df['date']).astype(int)

		# get everything except prices as data
		X = df.iloc[:, np.arange(0, 2).tolist() +
				np.arange(3, df.shape[1]).tolist()]
		#X = df.iloc[:, 3:]

		# get prices as our target
		y = df.iloc[:, 2]
		# turn into 2D array from 1D
		y = y.values.reshape(-1, 1)
	elif dataset == 'cali':
		df = pandas.read_csv(CALI_CSV)
		# convert dates to integers
		df['TIMESTAMP'] = df['TIMESTAMP'].astype(int)

		# get everything except wind power generation as data
		X = df.iloc[:, 0:-1]
		#X = df.iloc[:, 3:]

		# get prices as our target
		y = df.iloc[:, -1]
		# turn into 2D array from 1D
		y = y.values.reshape(-1, 1)
	else:
		print('ERROR: no implemented dataset specified. you must '
			'specify an implemented dataset (e.g., house, cali)!')
		exit()


	return X, y


# do_feature_scaling()
#
# preforms feature scaling on data and returns it
#
# input: data
# output: data feature scaled
#
def do_feature_scaling(data):
	# perform feature scaling on data
	sc = StandardScaler()
	sc.fit(data)

	return sc.transform(data)


# print_settings()
#
# input: arguments
# output: prints what arguments are passed to the method
#
def print_settings(args):
	if args.method == 'linear':
		print('no settings used...')
	elif args.method == 'ransac':
		print('random_state:\t{0}\nmax_trials:\t{1}\n'
			'min_samples:\t{2}\nloss:\t{3}\n'
			'residual_threshold:\t{4}\n'
			''.format(args.random_state, args.max_trials,
					args.min_samples, args.loss,
					args.residual_threshold))
	elif args.method == 'lasso':
		print('alpha:\t{0}\n'.format(args.alpha))
	elif args.method == 'ridge':
		print('alpha:\t{0}\n'.format(args.alpha))
	else:
		print('cannot print settings for method \'{0}\''
			''.format(args.method))


# store_results()
#
# input: the results dict to store results in, time it took to train,
# 	time it took to test, mean squared error, r2 score
# output: the results are stored in the results dict
#
def store_results(results, train_t, test_t, mse_train, mse_test, r2_train,
			r2_test):
	results['train_t'] = train_t
	results['test_t'] = test_t
	results['mse_train'] = mse_train
	results['mse_test'] = mse_test
	results['r2_train'] = r2_train
	results['r2_test'] = r2_test


# print_results()
#
# input: results dict, script mode (args.t)
# output: prints the results dict to the screen either in script-friendly mode
#	or human-readable mode
#
def print_results(results, script_mode=0):
	# print if script mode is on (==1)
	if script_mode:
		# print results for script friendliness
		for key, value in results.items():
			print(value, end='\t')
	else:
		print('results:')
		for key, value in results.items():
			print('\t{0}:\t{1}'.format(key, value))
		


# test_method()
#
# input: arguments, results dict, X (data), y (target)
# output: stores statistic results in results
#
def test_method(args, results, X, y):
	# initialize the method to correct one given the name
	method = None
	if args.method == 'linear':
		method = mylinear.skLR()
	elif args.method == 'ransac':
		method = myransac.skRANSAC(max_trials_=args.max_trials,
				min_samples_=args.min_samples, loss_=args.loss,
				residual_threshold_=args.residual_threshold,
				random_state_=args.random_state)
	elif args.method == 'ridge':
		method = myridge.skRidge(alpha_=args.alpha)
	elif args.method == 'lasso':
		method = mylasso.skLasso(alpha_=args.alpha)
	else:
		print('ERROR: method \'{0}\' not implemented yet.'
			''.format(args.method))
		exit()

	# *** DATA PREPROCESSING ***
	# split newly aquired X and y into seperate datasets for training and testing
	X_train, X_test, y_train, y_test = train_test_split(X, y,
						test_size=0.3, random_state=1)
	# perform feature scaling
	X_train_std = do_feature_scaling(X_train)
	X_test_std = do_feature_scaling(X_test)
	y_train_std = do_feature_scaling(y_train).flatten()
	y_test_std = do_feature_scaling(y_test).flatten()


	# *** TRAIN ***
	begin_t = time.time()
	# use feature scaled data for these specific methods
	#if args.method == 'linear' or args.method == 'ransac':
#		method.fit(X_train_std, y_train_std)
	method.fit(X_train_std, y_train_std)

	end_t = time.time()
	train_t = end_t - begin_t


	# *** TEST ***
	begin_t = time.time()
	# actually test and get result
	y_train_std_pred = method.predict(X_train_std)
	y_test_std_pred = method.predict(X_test_std)
	end_t = time.time()
	test_t = end_t - begin_t

	# get results
	mse_train = method.mse(y_train_std, y_train_std_pred)
	mse_test = method.mse(y_test_std, y_test_std_pred)
	r2_train = method.r2(y_train_std, y_train_std_pred)
	r2_test = method.r2(y_test_std, y_test_std_pred)

	store_results(results, train_t, test_t, mse_train, mse_test, r2_train,
		r2_test)


# -------------------------------------
#		BEGIN
# -------------------------------------

# get our command-line arguments.
args = get_args()
# extract data into X (data) and y (labels) from the given dataset
X, y = prepare_data(dataset=args.dataset)

# if script mode isn't enabled, then print settings
if args.t != 1:
	# print settings
	print_settings(args)

# results dict contains mse, r2, and time values
results = {
	'train_t':-1,
	'test_t':-1,
	'mse_train': -1,
	'mse_test': -1,
	'r2_train': -1,
	'r2_test': -1
}

# get our results
test_method(args, results, X, y)
# print results
print_results(results, args.t)





