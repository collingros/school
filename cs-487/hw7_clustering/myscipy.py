# collin gros
# 04-19-2021
# cs-487
# hw7
#
#
# myscipy.py
#
# this file contains the code for using scipy's linkage with
# scipy.
#
# NOTE: if things look weird, make your tabsize=8
#

from scipy.cluster.hierarchy import linkage
from scipy.cluster.hierarchy import fcluster


# class spLink
#
# this is the class used for performing linkage on training/testing
# data.
#
# is initialized with training data and training labels
# with the constructor()
#
class spLink:
	cluster = None

	# init()
	#
	# input: y(data), method (the method to use), metric (metric),
	#	optimal_ordering
	# output: self.cluster is setup with given values
	#
	# initializes the model with given values
	#
	def __init__(self, y_, method_, metric_, optimal_ordering_):
		self.cluster = linkage(y_, method=method_, metric=metric_,
					optimal_ordering=optimal_ordering_)


	# do_fcluster()
	#
	# input: the row cluster, and max_depth
	# output: self.cluster is changed to contain the final clusters
	#		from scipy's fcluster() function. criterion is set
	#		to distance.
	#
	def do_fcluster(self, row_cluster_, max_d_):
		self.cluster = fcluster(row_cluster_, max_d_,
					criterion='distance')









