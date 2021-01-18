#include <stdio.h>
#include <stdlib.h>

int main() {
	srand(0x61616161);
	for (int i = 0; i < 10; i++) {
		int guess = rand() % 6 + 1;
		printf("%d\n", guess);
	}

	return 0;
}

