#!/bin/bash
# collin gros
# 03-27-2021
#
# bash script for testing python code
#


for dataset in "iris" "digits" "mnist"
do
	rm $dataset.txt
	for dimreduc in "pca" "lda" "kpca"
	do
		echo -e -n "$dimreduc\t" >> $dataset.txt
		python3 main.py $dimreduc $dataset -t 1 -defaults=1 >> $dataset.txt
		echo "" >> $dataset.txt
	done
done
