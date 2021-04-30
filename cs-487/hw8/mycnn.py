# collin gros
# 04-30-2021
# cs-487
# hw8
#

import tensorflow as tf

NUM_EPOCHS = 20


class myCNN:
	def __init__(self, args_dict):
		# for use later with iterating args dict
		CONV_ARGS_ITR = [
			'filters', 'kernel_size', 'strides'
		]
		POOL_ARGS_ITR = [
			'pool_size'
		]

		# initialize the model with arguments
		self.model = tf.keras.Sequential()
		for i in range(0, args_dict['n']):
			# add Conv layer
			self.model.add(tf.keras.layers.Conv2D(
				filters=args_dict['filters'][i],
				kernel_size=args_dict['kernel_size'][i],
				strides=args_dict['strides'][i],
				padding='same',
				data_format='channels_last',
				activation='relu'
			))
			# add pool
			self.model.add(tf.keras.layers.MaxPool2D(
				pool_size=args_dict['pool_size'][i]
			))

		self.model.add(tf.keras.layers.Flatten())

		self.model.add(tf.keras.layers.Dense(
			units=1024, name='fc_1', activation='relu'
		))

		self.model.add(tf.keras.layers.Dropout(
			rate=0.5
		))
		self.model.add(tf.keras.layers.Dense(
			units=10, name='fc_2', activation='softmax'
		))

		tf.random.set_seed(1)

		self.model.build(input_shape=(None, 28, 28, 1))


		# build
		self.model.compile(
			optimizer=tf.keras.optimizers.Adam(),
			loss=tf.keras.losses.SparseCategoricalCrossentropy(),
			metrics=['accuracy']
		)


	def fit(self, train_data, valid_data):
		history = self.model.fit(
			train_data, epochs=NUM_EPOCHS,
			validation_data=valid_data,
			shuffle=True)
			
