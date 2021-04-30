# collin gros
# 04-30-2021
# cs-487
# hw8
#
# this program loads the MNIST dataset and runs a CNN on it.
#

import mycnn
import tensorflow_datasets as tfds
import tensorflow as tf
import argparse


BUFFER_SIZE = 10000
BATCH_SIZE = 64


def get_args():
	parser = argparse.ArgumentParser()

	parser.add_argument('-n')
	parser.add_argument('-filters', type=str,
		help='list of filters. use like \'32x64\' to make the list'
			'32, 64')
	parser.add_argument('-kernel_size', type=list,
		help='size for kernel. use like \'5555\' for a tuple list '
			'of (5, 5), (5, 5)')
	parser.add_argument('-strides', type=list,
		help='size for strides. use like \'5555\' for a tuple list '
			'of (5, 5), (5, 5)')
	parser.add_argument('-pool_size', type=list,
		help='size for pools. use like \'2233\' for a tuple list '
			'of (2, 2), (3, 3)')
	parser.add_argument('-defaults', type=int, help='use 1 for turning '
		'on default values')

	args = parser.parse_args()


	args_dict = {
		'n':2,

		'filters':[32, 64],
		'kernel_size':[(5, 5), (5, 5)],
		#'kernel_size':[(5, 5), (5, 5)],
		'strides':[(1, 1), (1, 1)],

		'pool_size':[(1, 1), (1, 1)]
	}
	# set defaults if applicable
	if args.defaults == 1:
		args_dict['n'] = 2
		args_dict['filters'] = [32, 64]
		args_dict['kernel_size'] = [(5, 5), (5, 5)]
		args_dict['strides'] = [(1, 1), (1, 1)]
		args_dict['pool_size'] = [(2, 2), (2, 2)]

	else: 
		args_dict['n'] = 2

		# process filters argument
		filters = args.filters.split('x')
		args_dict['filters'] = filters

		# process kernel_size argument
		kernel_size = []
		for i in range(len(args.kernel_size)):
			# get every two values
			if i % 2 != 0:
				continue
			kernel_size.append((args.kernel_size[i],
				 args.kernel_size[i+1]))
			i += 1
		args_dict['kernel_size'] = kernel_size

		# process strides argument
		strides = []
		for i in range(len(args.strides)):
			# get every two values
			if i % 2 != 0:
				continue
			strides.append((args.strides[i],
				 args.strides[i+1]))
			i += 1
		args_dict['strides'] = strides

		# process pool_size argument
		pool_size = []
		for i in range(len(args.pool_size)):
			# get every two values
			if i % 2 != 0:
				continue
			pool_size.append((args.pool_size[i],
				 args.pool_size[i+1]))
			i += 1
		args_dict['pool_size'] = pool_size


	return args_dict


def load_MNIST():
	# from ch15_CNN2: load the data
	mnist_bldr = tfds.builder('mnist')
	mnist_bldr.download_and_prepare()
	datasets = mnist_bldr.as_dataset(shuffle_files=False)
	mnist_train_orig, mnist_test_orig = datasets['train'], datasets['test']

	# from ch15_CNN2: preprocessing
	mnist_train = mnist_train_orig.map(
		lambda item:
			(tf.cast(item['image'], tf.float32)/255.0,
			# RGB value range [0,255]
			tf.cast(item['label'], tf.int32)
		)
	)
	mnist_test = mnist_test_orig.map(
		lambda item:
			(tf.cast(item['image'], tf.float32)/255.0,
			# RGB value range [0,255]
			tf.cast(item['label'], tf.int32)
		)
	)

	# from ch15_CNN2: seperating validation dataset from training data
	mnist_train = mnist_train.shuffle(buffer_size=BUFFER_SIZE,
		reshuffle_each_iteration=False)
	mnist_valid = mnist_train.take(10000).batch(BATCH_SIZE)
	mnist_train = mnist_train.skip(10000).batch(BATCH_SIZE)

	return mnist_train, mnist_valid


# BEGIN
# load training/validation data
mnist_train, mnist_valid = load_MNIST()


# get arguments
args_dict = get_args()

# create the CNN model
model = mycnn.myCNN(args_dict)
model.fit(mnist_train, mnist_valid)










