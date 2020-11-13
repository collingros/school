#!/bin/bash
# collin gros
# 11-13-2020
# cs471
# concurrency
#
#
# script is used to compile and run Concurrency.java, and passes
# its first command line argment to Concurrency.java.
#
# mainly made this because it sucks having to manually enter the commands
# to compile and run. (poor pinkies)

javac Concurrency.java && java Concurrency $1
