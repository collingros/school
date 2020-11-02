#!/usr/bin/perl
# collin gros
# 11-01-2020
#
# cs471
# File conversion -- remove control blocking data from backups
#
#
# this program, written in perl, removes extraneous data from a text
# file that was added from a backup program.
#
# the task for this assignment is to complete the above in python, perl,
# and java. this is my perl implementation.
#
#
# the pattern of the corrupt data:
# 		always starts with	^C
# 		always ends with	^B
# 		at most, 4 \n are introduced with each event
#			note: there may be more ^C after the initial ^C.
#

# filename of file to be fixed
my $FIX_NAME = "test-1.txt";
my $TMP_NAME = ".${FIX_NAME}.swp";


# overwrite tmp file to prepare for later
open(tfh, '>', $TMP_NAME) or die $!;
close(tfh);

# open fix file for reading
open(ffh, '<', $FIX_NAME) or die $!;
# open tmp file for appending
open(tfh, '>>', $TMP_NAME) or die $!;

my @stuff = do { local $/ = 1; <ffh>; };
foreach $thing (@stuff) {
	print "beg\n";
	print ${thing};
	print "end\n";
}




close(ffh);
close(tfh);
