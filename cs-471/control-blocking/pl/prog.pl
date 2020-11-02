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
my $FIX_NAME = "control-char.txt";
my $TMP_NAME = ".${FIX_NAME}.swp";


# overwrite tmp file to prepare for later
open(tfh, '>', $TMP_NAME) or die $!;
close(tfh);

# open fix file for reading
open(ffh, '<', $FIX_NAME) or die $!;
# open tmp file for appending
open(tfh, '>>', $TMP_NAME) or die $!;


# read file character by character until we hit eof
read ffh, my $c, 1;
until (ord $c == 0) {
	# if c is ^C then we start skipping
	if (ord $c == 3) {
		# skip characters up until eof or ^B
		until (ord $c == 0 or ord $c == 2) {
			# next character
			read ffh, $c, 1;
		}
		# skip the ^B
		read ffh, $c, 1;
	}

	# append good data to temporary file
	print tfh $c;

	# next character
	read ffh, $c, 1;
}


close(ffh);
close(tfh);

# overwrite bad file with fixed file
`mv $TMP_NAME $FIX_NAME`;

