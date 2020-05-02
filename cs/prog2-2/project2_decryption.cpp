/*	collin gros
	04/21/2020	*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>

#define MAX_ARG_SIZE 100


int parseArgs(int argc, char **argv, char *enc, char *pub,
				char *msg)
{
	if (argc != 4) {
		printf("ERROR: usage: [signedAndEncryptedFilename] "
				"[mypubkeyfilename] [symmetric key]\n");
		return 1;
	}

	sprintf(enc, "%s", argv[1]);
	sprintf(pub, "%s", argv[2]);
	sprintf(msg, "%s", argv[3]);

	return 0;
}


int main(int argc, char **argv)
{
	char encFilename[MAX_ARG_SIZE];
	char pubKeyFilename[MAX_ARG_SIZE];
	char symKeyFilename[MAX_ARG_SIZE];

	// parse our arguments, exit on failure
	if (parseArgs(argc, argv, encFilename, pubKeyFilename,
					symKeyFilename)) {
		printf("ERROR: parseArgs() failed!\n");
		exit(1);
	}

	printf("recieved arguments:\n\tencFilename: %s\n\t"
			"pubKeyFilename: %s\n\tsymKeyFilename: %s\n\n",
			encFilename, pubKeyFilename, symKeyFilename);

	printf("verifying the signed file with public key...");
	/*	verify the signed file with the public key	*/
	char buf[100 + MAX_ARG_SIZE];
	sprintf(buf, "openssl dgst -sha256 -verify %s "
			"-signature %s encrypted.txt", pubKeyFilename,
			encFilename);
	system(buf);
	printf("done\n\n");

	printf("using %s as key to decrypt %s using AES and putting it in "
			"plaintext.txt...",
			symKeyFilename, encFilename);
	/*	do the final decryption step by using the content of
		symmetric.txt and return the text file, containing
		the info and evaluation, in plaintext.
		can use the openssl command with system function.	*/	
	sprintf(buf, "openssl enc -d -aes-256-cbc -in "
			"encrypted.txt -out plaintext.txt "
			"-pass file:%s", symKeyFilename);
	system(buf);
	printf("done\n\n");

	printf("decryption finished\n");
}


