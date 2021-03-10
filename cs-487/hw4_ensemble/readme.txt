collin gros
03-10-2021
cs-487
hw4_ensemble


to run my code, do
	python3 main.py [classifier] [dataset] -[classifier args]
to see classifier names, dataset names, and classifier arg names, do
	python3 main.py -h

to use the kidney dataset, you need to have the dataset extracted in the
same directory as main.py, with the data being at:
	./Chronic_Kidney_Disease/chronic_kidney_disease.arff

EXAMPLES
	to train/test on the IRIS dataset and use AdaBoost with default
	classifier arguments, do
		python3 main.py adaboost iris -defaults=1
