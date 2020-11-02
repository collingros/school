# collin gros
# 11-01-2020
#
# cs471
# File conversion -- remove control blocking data from backups
#
#
# this program, written in python, removes extraneous data from a text
# file that was added from a backup program.
#
# the task for this assignment is to complete the above in python, perl,
# and java. this is my python implementation.
#
#
# the pattern of the corrupt data:
# 		always starts with	^C
# 		always ends with	^B
# 		at most, 4 \n are introduced with each event
#			note: there may be more ^C after the initial ^C.
#

# copy()
import shutil

# name of file we want to fix
FILE_NAME = 'control-char.txt'
#FILE_NAME = 'test-1.txt'


# strip_junk:
# 		opens the given filename and copies all non-junk to a temporary
#		file, which is moved and overwrites the given filename
# pre: fname is the name of the file to open and read.
# post: filename is stripped of all junk
def strip_junk(fname):
	tname = "." + fname + ".swp"
	ffile = open(fname, 'r')

	# create new empty file, or overwrite last tmp file
	tfile = open(tname, 'w')
	tfile.close()

	# begin reading file to change
	c = ffile.read(1)
	while c != '':
		# if c is ^C then we start skipping
		if ord(c) == 3:
			# skip characters up until eof or ^B
			while c != '' and ord(c) != 2:
				c = ffile.read(1)
			# skip the ^B
			c = ffile.read(1)

		# append good data to temporary file
		tfile = open(tname, 'a')
		tfile.write(c)
		tfile.close()

		# get next character
		c = ffile.read(1)

	ffile.close()

	# overwrite bad file with fixed file
	shutil.move(tname, fname)


strip_junk(FILE_NAME)









