#!/bin/bash

dirname=results-1nn
mkdir $dirname
for results in "iris.txt" "digits.txt" "mnist.txt"
do
	cat $results | awk -vORS=, '{print $2}' | sed 's/,$/\n/' \
		> $dirname/$results-train
	cat $results | awk -vORS=, '{print $3}' | sed 's/,$/\n/' \
		> $dirname/$results-test
	cat $results | awk -vORS=, '{print $4}' | sed 's/,$/\n/' \
		> $dirname/$results-acc
done
