# Reverse Engineering Room
"This room focuses on teaching the basics of assembly through reverse engineering"

## crackme1
"This first crackme file will give you an introduction to if statements and basic function calling in assembly."

Notes:

* ran binary and see we need to enter the correct password
* open gdb and look for ```strcmp``` function
	* the values to be compared are normally stored in buffers (i.e. registers)
	* we can print out these values easily


solution 1: print register in gdb

```
(gdb) x/s $rbp-0x14
0x7fffffffe09c: "hax0r"
```

solution 2: run strings


## crackme2
"This is the second crackme file - Unlike the first file, this will involve examining registers, how and where values are compared"

solution: look at the ```cmp``` instruction

```
0x0000000000000758 <+62>:    cmp    eax,0x137c

(gdb) print 0x137c
$1 = 4988
```

## crackme3
"This crackme will be significantly more challenging - it involves learning how loops work, and how they are represented in assembly"

Opened gdb and set a breakpoint on this line:

```
   0x000055555555477c <+98>:    cmp    dl,al
```

Ran program, reached breakpoint, and printed values in dl and al
If dl and al match, the loop continues, otherwise the program returns
Looked up the hex values in an ascii table
Pieced together the three letter password
