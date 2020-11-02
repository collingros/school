/*
collin gros
11-01-2020

cs471
File conversion -- remove control blocking data from backups


this program, written in java, removes extraneous data from a text
file that was added from a backup program.

the task for this assignment is to complete the above in python, perl,
and java. this is my java implementation.


the pattern of the corrupt data:
		always starts with	^C
		always ends with	^B
		at most, 4 \n are introduced with each event
			note: there may be more ^C after the initial ^C.
*/

import static java.nio.file.StandardOpenOption.*;
import java.nio.file.*;
import java.io.*;


class Prog
{
	// file we want to fix
	static String FILE_NAME = "control-char.txt";

	public static void main(String[] args)
	{
		// tmp file for writing
		String TMP_NAME = "." + FILE_NAME + ".swp";

		try {
			// open new readers/writers for reading the bad file (FILE_NAME)
			// and writing to a tmp file to be moved later (TMP_NAME)
			BufferedReader reader = new BufferedReader(new FileReader(FILE_NAME));
			BufferedWriter writer = new BufferedWriter(new FileWriter(TMP_NAME));

			// read bad file char-by-char
			for (int c = reader.read(); c != -1; c = reader.read()) {
				// if c is ^C then we start skipping
				if (c == 3) {
					// skip characters up until eof or ^B
					for (;c != -1 && c != 2; c = reader.read());
					// skip the ^B
					c = reader.read();
				}

				// append good data to temporary file (not actually written yet)
				writer.write(c);
			}

			// flush the buffer so it writes
			writer.close();
			reader.close();

			// replace bad file with good file
			Path ffile = Paths.get(FILE_NAME);
			Path tfile = Paths.get(TMP_NAME);
			Files.move(tfile, ffile, StandardCopyOption.REPLACE_EXISTING);
		}
		catch (IOException e) {
			System.err.println(e);
		}
	}
}


