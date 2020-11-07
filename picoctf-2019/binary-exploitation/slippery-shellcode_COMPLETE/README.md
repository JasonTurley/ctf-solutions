## slippery-shellcode

In this program, a random location in the buffer is selected and executed.

Fill the buffer with all nop operations, so any location chosen will trigger our
nop sled, and thus execute the shellcode.

Since the program terminates after shellcode injection, run the program like so:

```(python exploit.py; cat -) | ./vuln```

```cat flag.txt```
