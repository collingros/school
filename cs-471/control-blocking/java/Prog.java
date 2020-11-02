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

//import static java.nio.file.StandardOpenOption.*;
import java.nio.file.*;
import java.io.*;


class Prog
{
	// file we want to fix
	static String FILE_NAME = "test-1.txt";

	public static void main(String[] args)
	{
		// tmp file for writing
		String TMP_NAME = "." + FILE_NAME + ".swp";

/*
		Path tpath = Paths.get(TMP_NAME);
		// open tmp file for appending
		OutputStream out;
		try (out = new BufferedOutputStream(
					Files.newOutputStream(tpath, CREATE, APPEND))) {
		}
		catch (IOException e) {
			System.err.println(e);
		}
*/

		// open bad file for reading
		Path fpath = Paths.get(FILE_NAME);
		BufferedReader reader;
		try {
			InputStream fin = Files.newInputStream(fpath);
			reader = new BufferedReader(new InputStreamReader(fin));
		}
		catch(IOException e) {
			System.err.println(e);
		}

		// read bad file char-by-char
		for (int c = reader.read(); c != -1; c = reader.read()) {
			// if c is ^C then we start skipping
			if (c == 3) {
				// skip characters up until eof or ^B
				for (;c != -1 && c != 2; c = reader.read());
				// skip the ^B
				c = reader.read();
			}

			// append good data to temporary file
			System.out.print((char) c);
		}

/*
		// open bad file for reading
		Path fpath = Paths.get(FILE_NAME);
		try {
			InputStream fin = Files.newInputStream(fpath);
			BufferedReader reader = new BufferedReader(new InputStreamReader(fin));
			// read bad file char-by-char
			for (int c = reader.read(); c != -1; c = reader.read()) {
				// if c is ^C then we start skipping
				if (c == 3) {
					// skip characters up until eof or ^B
					for (;c != -1 && c != 2; c = reader.read());
					// skip the ^B
					c = reader.read();
				}

				// append good data to temporary file
				System.out.print((char) c);
			}
		}
		catch(IOException e) {
			System.err.println(e);
		}
	*/
	}
}


