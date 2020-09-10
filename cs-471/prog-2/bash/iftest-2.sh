#!/bin/bash
#
# collin gros
# 09-09-2020
#
# this program tests whether the bourne shell will do
# short-circuit evaluation in if statements
#


# makes a file, called-echoTrue, and echos true for substitution later
echoTrue ()
{
	echo true

	touch called-echoTrue
}


# will crete a file called called-echoTrue
if true && $(echoTrue); then
	exit
fi


