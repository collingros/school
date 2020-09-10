#!/usr/bin/perl
# collin gros
# 09-09-2020
#
# this program shows that perl short circuits if statements by proving
# perl does not move through a function if the first part of the statement
# is evaluated as false


# returns true and prints that we've gone through it
sub retTrue
{
	print "in retTrue\n";
	return 1;
}


# short circuits, retTrue is never called because the frist part of
# statement is eval as false, retTrue doesn't matter
if (0 and retTrue) {
	print "if\n";
}


