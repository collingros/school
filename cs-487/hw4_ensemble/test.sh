#!/bin/bash
# collin gros
# 03-10-2021
#
# bash script for testing python code
#

for dataset in "iris" "digits" "kidney"
do
	for classifier in "random_forest" "bagging" "adaboost"
	do
		echo "***$dataset:$classifier***" >> results.txt
		python3 main.py $classifier $dataset -defaults=1 >> results.txt
	done
done
