collin gros
03-27-2021
cs-487
hw5


to run my code, do
	python3 main.py [dimension reduction name] [dataset] -[dimreduc args]
to see dimreduc names, dataset names, and dimreduc arg names, do
	python3 main.py -h

EXAMPLES
	to train/test on the MNIST dataset and use PCA with default
	arguments, do
		python3 main.py pca mnist -defaults=1
