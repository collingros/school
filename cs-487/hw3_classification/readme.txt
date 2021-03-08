collin gros
03-07-2021
cs-487
hw3


to run my code, do
	python3 main.py [classifier name] [dataset] [ARGS]
you can also specify to use the defaults with
	python3 main.py [classifier name] [dataset] -defaults=1
to see the possible argument names, do
	python3 main.py -h

the second dataset that i used was the one mentioned in the homework
problem description, the REALDISP Activity Recognition Dataset. my program
uses data from one subject.
to use this dataset, you have to extract the dataset in the same folder as
main.py, and make sure it is named "realistic_sensor_displacement".


EXAMPLES:
	python3 main.py dt iris -criterion=gini -max_depth=4 -random_state=1

OUTPUT:
	...beg [classifier name]...

	[classifier name]:\t[accuracy]

	elapsed:\t[time elapsed (in seconds)]

	...end [classifier name]...

