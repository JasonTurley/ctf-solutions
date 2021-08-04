// crackme6.c - reverse engineered crackme6 binary into valid C code
// gcc -Wall -Werror -Wextra crackme6.c -o rev-crackme
#include <stdio.h>
#include <stdlib.h>

// Check each character to see if user entered correct password
int my_secure_test(char *guess)
{
	// List of hex values: [0x31, 0x33, 0x33, 0x37, 0x5f, 0x70, 0x77, 0x64]
	if (guess[0] != 0x31)
		return -1;
	if (guess[1] != 0x33)
		return -1;
	if (guess[2] != 0x33)
		return -1;
	if (guess[3] != 0x37)
		return -1;
	if (guess[4] != 0x5f)
		return -1;
	if (guess[5] != 0x70)
		return -1;
	if (guess[6] != 0x77)
		return -1;
	if (guess[7] != 0x64)
		return -1;

	return 0;
}

int compare_pwd(char* guess)
{
	int retval = my_secure_test(guess);

	if (retval != 0) {
		printf("password \"%s\" not OK\n", guess);
		return 0;
	}

	printf("password OK");

	return 0;
}

int main(int argc, char *argv[])
{
	// Check that we entered a password as a command line arg
	if (argc < 2) {
		printf("Usage : %s password\nGood luck, read the source\n", argv[0]);
		return 0;
	}

	// Check if user entered correct password
	// TODO: check if int or char value
	
	compare_pwd(argv[1]);

	return 0;
}
