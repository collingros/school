/*	collin gros
	04/21/2020	*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>

#define MAX_ARG_SIZE 100


int parseArgs(int argc, char **argv, char *pub)
{
	if (argc != 2) {
		printf("ERROR: usage: [pubkeyfilename]\n");
		return 1;
	}

	sprintf(pub, "%s", argv[1]);

	return 0;
}


int main(int argc, char **argv)
{
	char pubKeyFilename[MAX_ARG_SIZE];

	// parse our arguments, exit on failure
	if (parseArgs(argc, argv, pubKeyFilename)) {
		printf("ERROR: parseArgs() failed!\n");
		exit(1);
	}

	/*	verify the signed file with the public key	*/
	char buf[100 + MAX_ARG_SIZE];
	sprintf(buf, "openssl dgst -sha256 -verify %s "
			"-signature encrypt_me.txt.enc.sha256 "
			"encrypt_me.txt.enc", pubKeyFilename);
	system(buf);

	/*	do the final decryption step by using the content of
		symmetric.txt and return the text file, containing
		the info and evaluation, in plaintext.
		can use the openssl command with system function.	*/	
	sprintf(buf, "openssl enc -d -aes-256-cbc -in "
			"encrypt_me.txt.enc -out plaintext.txt "
			"-pass file:symmetric.txt");
	system(buf);
}


