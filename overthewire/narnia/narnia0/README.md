# Narnia0
Connect to the challenge server:
```ssh narnia0@ narnia.labs.overthewire.org 2226```

## Objective
Change the target variable to 0xdeadbeef.

## Solution
```c
#include <stdio.h>
#include <stdlib.h>

int main(){
    long val=0x41414141;
    char buf[20];

    printf("Correct val's value from 0x41414141 -> 0xdeadbeef!\n");
    printf("Here is your chance: ");
    scanf("%24s",&buf);

    printf("buf: %s\n",buf);
    printf("val: 0x%08x\n",val);

    if(val==0xdeadbeef){
        setreuid(geteuid(),geteuid());
        system("/bin/sh");
    }
    else {
        printf("WAY OFF!!!!\n");
        exit(1);
    }

    return 0;
}
```

```val``` is placed directly under the buffer on the stack. Fill the buffer with 20 bytes of data and 0xdeadbeef to overwrite the value.
