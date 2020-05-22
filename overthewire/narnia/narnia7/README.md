# narnia7
The objective of this challenge is to change the function pointer ptrf() to
point to hackedfunction() instead of goodfunction().

This is accomplished with a format string exploit.

## Notes

Source code for the vulnerable function, vuln():
```*.c
int vuln(const char *format){
        char buffer[128];
        int (*ptrf)();

        memset(buffer, 0, sizeof(buffer));
        printf("goodfunction() = %p\n", goodfunction);
        printf("hackedfunction() = %p\n\n", hackedfunction);

        ptrf = goodfunction;
        printf("before : ptrf() = %p (%p)\n", ptrf, &ptrf);

        printf("I guess you want to come to the hackedfunction...\n");
        sleep(2);
        ptrf = goodfunction;

        snprintf(buffer, sizeof buffer, format);

        return ptrf();
}
```
A buffer of size 128 is declared and zeroed out with ```memset```. The
exploitable ```snprinf``` function is called, so I know this is a format string
exploit.

The function prints:
```
goodfunction() = 0x80486ff
hackedfunction() = 0x8048724

before : ptrf() = 0x80486ff (0xffffd5c8)
```


However, the buffer is not printed out, so we cannot see the target address.
Time to play around with gdb!


In gdb-peda I set a breakpoint immediately after the call to ```snprintf```
(0x080486b2), and examined 24 words as hex from the stack.

```
[------------------------------------stack-------------------------------------]
0000| 0xffffd60c --> 0xffffd61c ("AAAABBBBCCCCDDDDEEEEFFFF")
0004| 0xffffd610 --> 0x80
0008| 0xffffd614 --> 0xffffd882 ("AAAABBBBCCCCDDDDEEEEFFFF")
0012| 0xffffd618 --> 0x80486ff (<goodfunction>:	push   ebp)
0016| 0xffffd61c ("AAAABBBBCCCCDDDDEEEEFFFF")
0020| 0xffffd620 ("BBBBCCCCDDDDEEEEFFFF")
0024| 0xffffd624 ("CCCCDDDDEEEEFFFF")
0028| 0xffffd628 ("DDDDEEEEFFFF")
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value

Breakpoint 3, 0x080486b2 in vuln ()
gdb-peda$ x/24wx 0xffffd60c
0xffffd60c:	0xffffd61c	0x00000080	0xffffd882	0x080486ff
0xffffd61c:	0x41414141	0x42424242	0x43434343	0x44444444
0xffffd62c:	0x45454545	0x46464646	0x00000000	0x00000000
0xffffd63c:	0x00000000	0x00000000	0x00000000	0x00000000
0xffffd64c:	0x00000000	0x00000000	0x00000000	0x00000000
0xffffd65c:	0x00000000	0x00000000	0x00000000	0x00000000
gdb-peda$
```

* 0xffffd61c is the address of our string passed from argv[1]
* 0x00000080 = 128, the size of the buffer
* 0xfffd882 is the address of ptrf (&ptrf)
* 0x080486ff is the address of the goodfunction() and what ptrf() initial points
* to

