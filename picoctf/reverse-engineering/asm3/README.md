# asm3

## Description
What does asm3(0xd2c26416,0xe6cf51f0,0xe54409d5) return? Submit the flag as a
hexadecimal value (starting with '0x'). NOTE: Your submission for this
question will NOT be in the normal flag format.

**Category:** Reverse Engineering

**Points:** 300

## Source Code
Comments added:

```
asm3(0xd2c26416,0xe6cf51f0,0xe54409d5) --> asm3(3535954966, 3872346608, 3846441429)

asm3:
	<+0>:	push   ebp			; set up stack frame
	<+1>:	mov    ebp,esp
	<+3>:	xor    eax,eax			; clear out eax to 0
	<+5>:	mov    ah,BYTE PTR [ebp+0x9]	; ah = 0xc2
	<+8>:	shl    ax,0x10			; ax = 0x0000 (ah now = 0x0)
	<+12>:	sub    al,BYTE PTR [ebp+0xe]	; al = 0x0 - 0x51 = 0xaf??
	<+15>:	add    ah,BYTE PTR [ebp+0xf]	; ah = 0x0 + 0xf0 = 0xf0
	<+18>:	xor    ax,WORD PTR [ebp+0x12]
	<+22>:	nop
	<+23>:	pop    ebp
	<+24>:	ret
```

## Solution
After 40 minutes of trying to solve this challenge by hand on a whiteboard, I
instead compiled and ran it with help from [this writeup from
Dvd848](https://github.com/Dvd848/CTFs/blob/master/2019_picoCTF/asm3.md).

### Compile and Run
Modify ```test.S```:
```
.intel_syntax noprefix
.global asm3

asm3:
        push   ebp
        mov    ebp,esp
        xor    eax,eax
        mov    ah,BYTE PTR [ebp+0x9]
        shl    ax,0x10
        sub    al,BYTE PTR [ebp+0xe]
        add    ah,BYTE PTR [ebp+0xf]
        xor    ax,WORD PTR [ebp+0x12]
        nop
        pop    ebp
        ret
```

Next, create ```main.c```:
```
#include <stdio.h>

int asm3(int, int, int);

int main() {
    printf("The flag is 0x%x\n", asm3(0xd2c26416,0xe6cf51f0,0xe54409d5));
    return 0;
}
```

Finally, compile and run:
```
jason@lapras:$ gcc -masm=intel -m32 -c test.S -o test.o
jason@lapras:$ gcc -m32 -c main.c -o main.o
jason@lapras:$ gcc -m32 test.o main.o -o main
jason@lapras:$ ./main
The flag is 0x375
```
