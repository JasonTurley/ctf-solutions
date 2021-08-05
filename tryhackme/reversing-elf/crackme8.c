#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s password\n", argv[0]);
		return 1;
	}

	int retval = atoi(argv[1]);

	printf("DEBUG: retval = %d\n", retval);

	if (retval != 0xcafef00d) {
		printf("Access denied.\n");
		return 1;
	}
	
	printf("Access granted.\n");
	// printf flag
	return 0;
}
