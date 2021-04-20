# collin gros
# 04-19-2021
# cs-487
# hw7
#
#
# NOTE: if things look weird, make your tabsize=8

import datetime as dt
# arg handling
import sys
import argparse

from sklearn import datasets

# the implemented algorithms
import mydbscan
import mykmeans
import myscikit
import myscipy

# for splitting data into training and testing data
from sklearn.model_selection import train_test_split
# for feature scaling
from sklearn.preprocessing import StandardScaler

# for timing
import time

# for handling dataset
import pandas
import numpy as np

# for graphs
import matplotlib.pyplot as plt


# filepaths for datasets
HOUSE_CSV = './house/house.csv'
CALI_CSV = './cali/cali.csv'


# return the arguments
def get_args():
	parser = argparse.ArgumentParser()
	parser.add_argument('method', help='what to use. can be kmeans, '
				'scikit, scipy, or dbscan')
	parser.add_argument('dataset', help='the dataset to use. can be iris'
				' or beans')

	# kmeans
	parser.add_argument('-n_clusters', type=int)
	parser.add_argument('-init')
	parser.add_argument('-n_init', type=int)
	parser.add_argument('-max_iter', type=int)
	parser.add_argument('-tol', type=float)
	parser.add_argument('-random_state', type=int)

	# scikit
	parser.add_argument('-affinity')
	parser.add_argument('-linkage')

	# scipy
	parser.add_argument('-linkage_method')
	parser.add_argument('-metric')
	parser.add_argument('-optimal_ordering', type=int)
	parser.add_argument('-max_d', type=float)

	# dbscan
	parser.add_argument('-eps', type=float)
	parser.add_argument('-min_samples', type=int)

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
		#kmeans
		args.n_clusters=3
		args.init='random'
		args.n_init=10
		args.max_iter=300
		args.tol=1e-04
		args.random_state=0

		#scikit
		args.affinity='euclidean'
		args.linkage='complete'

		#scipy
		args.method='single'
		args.metric='euclidean'
		args.optimal_ordering=0
		args.max_d=2.5

		#dbscan
		args.eps=0.2
		args.min_samples=5

		# disable script-friendly output
		args.t = 0

	return args


# prepare_data()
#
# input: either 'iris' or 'beans'
# output:
#	X, y tuple where X is data and y is the labels
#
def prepare_data(dataset=''):
	X = None
	y = None

	# handle specific datasets
	if dataset == 'iris':
		iris = datasets.load_iris()

		# only the first two features
		X = iris.data[:, :2]
		y = iris.target
	elif dataset == 'beans':
		printf('the beans dataset has not been implemented yet.')
		exit()
	else:
		print('ERROR: no implemented dataset specified. you must '
			'specify an implemented dataset (e.g., iris, beans)!')
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
	if args.method == 'kmeans':
		print('n_clusters: {0}\ninit: {1}\nn_init: {2}\n'
			'max_iter: {3}\ntol: {4}\nrandom_state: {5}'
			''.format(args.n_clusters, args.init, args.n_init,
				args.max_iter, args.tol, args.random_state))
	elif args.method == 'scikit':
		print('affinity: {0}\nlinkage: {1}'.format(args.affinity,
							args.linkage))
	elif args.method == 'scipy':
		print('linkage_method: {0}\nmetric: {1}\n'
			'optimal_ordering: {2}'.format(args.linkage_method,
			args.metric, args.optimal_ordering))
	elif args.method == 'dbscan':
		print('eps: {0}\nmin_samples: {1}'.format(args.eps,
				args.min_samples))
	else:
		print('cannot print settings for method \'{0}\''
			''.format(args.method))


# store_results()
#
# input: the results dict to store results in, time it took to train,
# 	time it took to test, sse, method name
# output: the results are stored in the results dict
#
def store_results(results, train_t, test_t, sse, method):
	results['train_t'] = train_t
	results['test_t'] = test_t
	results['sse'] = sse
	results['method_name'] = method


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
def test_method(method_name, args, results, X, y):
	# initialize the method to correct one given the name
	method = None
	if method_name == 'kmeans':
		method = mykmeans.skKMeans(args.n_clusters, args.init,
				args.n_init, args.max_iter, args.tol,
				args.random_state)
	elif method_name == 'scikit':
		method = myscikit.skAC(args.n_clusters, args.affinity,
				args.linkage)
	elif method_name == 'scipy':
		# can't initialize yet, need data
		pass
	elif method_name == 'dbscan':
		method = mydbscan.skDBSCAN(args.eps, args.min_samples,
				args.metric)
	else:
		print('ERROR: method \'{0}\' not implemented yet.'
			''.format(method))
		exit()

	# *** DATA PREPROCESSING ***
	# split newly aquired X and y into seperate datasets for training and testing
	X_train, X_test, y_train, y_test = train_test_split(X, y,
						test_size=0.3, random_state=1)

	# initialize scipy
	if method_name == 'scipy':
		method = myscipy.spLink(y_train, args.method, args.metric,
				args.optimal_ordering)

	# *** TRAIN ***
	begin_t = time.time()
	# treat scipy specially
	if method_name == 'scipy':
		pass
	else:
		method.fit(X_train, y_train)

	end_t = time.time()
	train_t = end_t - begin_t


	# *** TEST ***
	begin_t = time.time()
	# actually test and get result
	if method_name == 'scipy':
		method.do_fcluster(method.cluster, args.max_d)
	else:
		y_train_pred = method.predict(X_train)
		y_test_pred = method.predict(X_test)
	end_t = time.time()
	test_t = end_t - begin_t

	# get results
	# if we are using kmeans, we have sse
	sse = 0
	if method_name == 'kmeans':
		sse = method.sse()

	store_results(results, train_t, test_t, sse, method_name)


# graph_results()
#
# input: dataset name, results dict for each method, color for graph
# output: saves graphs comparing training times,
#	testing times, mse, and r2 for each method
#	on each dataset
#
def graph_results(dataset, all_results, color_):
	# all of the data to be plotted on Y axis
	data = {}
	# fill data dict with all test results
	for results in all_results:
		for key, value in results.items():
			print('key: {0}\tval: {1}'.format(key, value))
			try:
				data[key].append(value)
			except:
				data[key] = []
				data[key].append(value)

	print(data)

	# plot the data vs method used
	for key, value in data.items():
		# skip method_name
		if key == 'method_name':
			continue

		# set labels of axis/title
		plt.xlabel('Method Used')
		plt.ylabel(key)
		plt.title('{0}: {1} vs Method Used'.format(dataset, key))

		# plot data
		plt.bar(data['method_name'], value, color=color_)

		# replace spaces in Y label name with underscores for
		# the filename
		plt.savefig('{0}-{1}.png'.format(dataset, key))

		# write
		plt.show()
		# erase
		plt.clf()


# test_all()
#
# input: arguments
# output: runs all algorithms on datasets and saves graphs of the results
#
def test_all(args):
	methods = ['kmeans', 'scikit', 'scipy', 'dbscan']
	datasets = ['iris']
	# colors for the graph
	colors = ['b']

	for d in datasets:
		all_results = []
		X, y = prepare_data(dataset=d)
		for method in methods:
			print('now doing {0}.'.format(method))
			# results dict contains mse, r2, and time values
			results = {
				'train_t':-1,
				'test_t':-1,
				'sse': -1,
				'method_name':''
			}

			test_method(method, args, results, X, y)
			# add this current test to the list of test
			# results
			all_results.append(results)

		graph_results(d, all_results, colors[0])
	



# -------------------------------------
#		BEGIN
# -------------------------------------

# test all methods and graph all of them
#test_all(args)

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
	'sse': -1,
	'method_name':''
}

test_all(args)

# get our results
#test_method(args.method, args, results, X, y)
# print results
#print_results(results, args.t)









