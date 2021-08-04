# Reversing ELF

[Reversing ELF](https://tryhackme.com/room/reverselfiles) is a beginner Reverse
Engineering room from TryHackMe.

Note that all the correct passwords have been redacted.

## Crackme1

> Let's start with a basic warmup, can you run the binary?

This is the warmup challenge. Simply download and execute the binary file.

```
$ ./crackme1    
flag{REDACTED}
```

That was easy!

## Crackme2

> Find the super-secret password! and use it to obtain the flag

Run the binary.

```
$ ./crackme2                      
Usage: ./crackme2 password
```

Looks like we need to provide the password as a command line argument.

```
$ ./crackme2 abc123     
Access denied.
```

Hmm. Let's use `ltrace` to see what library calls the crackme is using.

```
$ ltrace ./crackme2 abc123
__libc_start_main(0x804849b, 2, 0xff8a03c4, 0x80485c0 <unfinished ...>
strcmp("abc123", "REDACTED_PASSWORD_HERE")                     = -1
puts("Access denied."Access denied.
)                                        = 15
+++ exited (status 1) +++
```

We see that our guess of "abc123" is being compared to "super_secret_password".
Since they differ, strcmp() returns -1 and the Access denied message is printed. 

Run the binary again with the hidden password.

```
$ ./crackme2 REDACTED_PASSWORD_HERE
Access granted.
flag{REDACTED}
```

## Crackme3

> Use basic reverse engineering skills to obtain the flag

We run the program and it mocks us for giving the wrong password.

```
$ ./crackme3 beans
Come on, even my aunt Mildred got this one!
```

Time to bust out the [radare2](https://github.com/radareorg/radare2) tool suite.
Check if there are any interesting plaintext strings in the file with rabin2.

```
$ rabin2 -z ./crackme3
[Strings]                                                                                            
nth paddr      vaddr      len size section type  string                                              
―――――――――――――――――――――――――――――――――――――――――――――――――――――――                                              
0   0x00000e68 0x08048e68 19  20   .rodata ascii Usage: %s PASSWORD\n                                
1   0x00000e7c 0x08048e7c 14  15   .rodata ascii malloc failed\n                                     
2   0x00000e8b 0x08048e8b 64  65   .rodata ascii ZjByX3kwdXJfNWVjMG5kX2xlNTVvbl91bmJhc2U2NF80bGxfN2gzXzdoMW5nNQ==                                                                                         
3   0x00000ed0 0x08048ed0 17  18   .rodata ascii Correct password!                                   
4   0x00000ef0 0x08048ef0 43  44   .rodata ascii Come on, even my aunt Mildred got this one!         
5   0x00000f1c 0x08048f1c 64  65   .rodata ascii ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/
```

There seems to be a base64 encoded string on line 2. Let's decode it.

```
$ echo "ZjByX3kwdXJfNWVjMG5kX2xlNTVvbl91bmJhc2U2NF80bGxfN2gzXzdoMW5nNQ==" | base64 -d
REDACTED_ANSWER
```

Sweet! Take that Mildred!

## Crackme4

> Analyze and find the password for the binary?

Run the crackme.

```
$ ./crackme4
Usage : ./crackme4 password
This time the string is hidden and we used strcmp
```

This time the binary tells us to look for the strcmp function. We can just use
`ltrace` again.

```
$ ltrace ./crackme4 AAAAAA           
__libc_start_main(0x400716, 2, 0x7ffcede30f08, 0x400760 <unfinished ...>
strcmp("THE_REDACTED_PASSWORD", "AAAAAA")					= 44
printf("password "%s" not OK\n", "AAAAAA"password "AAAAAA" not OK
)									= 25
+++ exited (status 0) +++
```

## Crackme5

> What will be the input of the file to get output "Good game"?


Time to ltrace.

```
$ ltrace ./crackme5                                                                                
__libc_start_main(0x400773, 1, 0x7fff41b6ac88, 0x4008d0 <unfinished ...>                             
puts("Enter your input:"Enter your input:                                                            
)                                     = 18                                                           
__isoc99_scanf(0x400966, 0x7fff41b6ab40, 0, 0x7fa283e16f33HELLO                                      
)   = 1                                                                                              
strlen("HELLO")                                               = 5                                    
strlen("HELLO")                                               = 5                                    
strlen("HELLO")                                               = 5                                    
strlen("HELLO")                                               = 5                                    
strlen("HELLO")                                               = 5                                    
strlen("HELLO")                                               = 5                                    
strncmp("HELLO", "REDACTED", 28)          = -7                                   
puts("Always dig deeper"Always dig deeper
```

Given a string of length N characters, the crackme calls strlen() N+1
times. It then calls strncmp() to check our value with the correct password. 

Once again, the password is visible in the ltrace output.

## Crackme6

> Analyze the binary for the easy password

Open the binary in radare2.

```
$ r2 -d ./crackme6
```

Next, analyze (`aaa`) and list (`afl`) all the functions. Examine the
function my_secure_test by entering `pdf @sym.my_secure_test`.

This is a long function but we only need to concern ourselves with the **cmp**
instructions. Each one compares $al (the lower 8-bits of register $rax) with a
single byte.

```
... redacted assembly ...
cmp	al, 0x31
...
cmp	al, 0x33
... more redacted assembly ...
```

I wrote a small python script that translates each hex value into an ASCII
character:

```
#!/usr/bin/env python3
data = [0x31, 0x33, 0x33, 0x37, 0x5f, 0x70, 0x77, 0x64]

for item in data:
    print(chr(item), end="")

print()
```

This prints the password on one line!

## Crackme7
