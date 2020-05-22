# narnia4

## Objective
Exploit the vulnerable ```strcpy``` function to overflow the buffer and spawn a
shell.

```c
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

extern char **environ;

int main(int argc,char **argv){
    int i;
    char buffer[256];
    for(i = 0; environ[i] != NULL; i++)
        memset(environ[i], '\0', strlen(environ[i]));
    if(argc>1)
        strcpy(buffer,argv[1]);
    return 0;
}
```

## Solution
Before ```strcpy``` is called, all of the environment variables are cleared.
Meaning, we cannot store the shellcode in an environment variables like in
narnia2.


Instead, we can store the shellcode in the provided buffer, and change the EIP
to point to the start of the buffer.


The address for the start of the buffer can be found with either ```ltrace``` or
```strace```.

## Notes and gotchas
- The fact that the buffer is 256 bytes is a sign that it should hold the
  shellcode. At first I was trying to fill the buffer with junk.
