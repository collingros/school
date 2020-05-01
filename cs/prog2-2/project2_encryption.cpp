/*	collin gros
	04/21/2020

	prog2-2 for CS478	*/

#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>

#define MAX_ARG_SIZE 100


int parseArgs(int argc, char **argv, char *msg, char *pub, char *pri)
{
	if (argc != 4) {
		printf("ERROR: usage: [msg] [pubkeyfilename] [privkeyfilename]\n");
		return 1;
	}

	sprintf(msg, "%s", argv[1]);
	sprintf(pub, "%s", argv[2]);
	sprintf(pri, "%s", argv[3]);

	return 0;
}


int main(int argc, char **argv)
{
	char msg[MAX_ARG_SIZE];
	char pubKeyFilename[MAX_ARG_SIZE];
	char priKeyFilename[MAX_ARG_SIZE];

	// parse our arguments, exit on failure
	if (parseArgs(argc, argv, msg, pubKeyFilename, priKeyFilename)) {
		printf("ERROR: parseArgs() failed!\n");
		exit(1);
	}

	/*	decrypt message with third party public key and store it
		in symmetric.txt	*/
	char buf[100 + MAX_ARG_SIZE * 3];
	sprintf(buf, "openssl rsautl -encrypt -raw -inkey "
			"%s -pubin -in %s -out symmetric.txt", pubKeyFilename, msg);
	system(buf);

	/*	use the decrypted message as a symm key to encrypt a text file
		with one of the symm key algos (AES or 3DES). write the code for
		this part OR use openssl command with system function.
		the text file MUST have my name and 800652097.
		explain which algo was used in project eval	*/
	sprintf(buf, "openssl aes-256-cbc -in encrypt_me.txt "
			"-out encrypt_me.txt.enc -pass file:symmetric.txt");
	system(buf);

	/*	sign the file content with our private key, and store
		it in a file	*/
	sprintf(buf, "openssl dgst -sha256 -sign %s -out "
			"encrypt_me.txt.enc.sha256 encrypt_me.txt.enc",
			priKeyFilename);
	system(buf);


	return 0;
}



