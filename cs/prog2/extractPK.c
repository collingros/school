/*	collin gros
	04/14/2020

	prog 2 assignment; extracts a public key and priv key from a given
	certificate	*/
#include <openssl/bio.h>


#define CERT_FILENAME	"cert.pem"


int main()
{
	/*	for reading/writing the file	*/
	BIO *certb = BIO_new(BIO_s_file());
	BIO *outb = BIO_new_fp(stdout, BIO_NOCLOSE);

	/*	attempt reading the cert, returns 0 for failure	*/
	if (!BIO_read_filename(certb, CERT_FILENAME)) {
		return 1;
	}

	return 0;
}
