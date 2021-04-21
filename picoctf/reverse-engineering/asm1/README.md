# asm1

## Description
> What does asm1(0x6fa) return? Submit the flag as a hexadecimal value (starting
> with '0x'). NOTE: Your submission for this question will NOT be in the normal
> flag format.

**Points:** 200

## Source Code

We are given the x86 assembly instructions for a function called asm1. I
added comments to get a better sense of what this function is doing:

```assembly
# ebp+0x8 stores function argument no. 1
# not sure what value is in ebp+0x8
asm1:
	<+0>:	push   ebp				; set up the stack frame
	<+1>:	mov    ebp,esp
	<+3>:	cmp    DWORD PTR [ebp+0x8],0x3a2	; cmp with 930
	<+10>:	jg     0x512 <asm1+37>
	<+12>:	cmp    DWORD PTR [ebp+0x8],0x358	; cmp with 856
	<+19>:	jne    0x50a <asm1+29>
	<+21>:	mov    eax,DWORD PTR [ebp+0x8]
	<+24>:	add    eax,0x12				; eax += 18
	<+27>:	jmp    0x529 <asm1+60>
	<+29>:	mov    eax,DWORD PTR [ebp+0x8]
	<+32>:	sub    eax,0x12				; eax -= 18
	<+35>:	jmp    0x529 <asm1+60>
	<+37>:	cmp    DWORD PTR [ebp+0x8],0x6fa	; cmp with 1786
	<+44>:	jne    0x523 <asm1+54>
	<+46>:	mov    eax,DWORD PTR [ebp+0x8]
	<+49>:	sub    eax,0x12				; eax -= 18
	<+52>:	jmp    0x529 <asm1+60>
	<+54>:	mov    eax,DWORD PTR [ebp+0x8]		; eax = ebp+0x8
	<+57>:	add    eax,0x12				; eax += 18
	<+60>:	pop    ebp				; clean up stack frame
	<+61>:	ret
```

My main hiccup for this problem was not knowing that value was in ebp+0x8. But
after re-reading the challenge description it shows that the value 0x6fa (1786)
is being passed as an argument.

## Solution
After knowing what value to work with, find the output became trivial. I have
included the code flow below:

```assembly
asm1:
	<+0>:	push   ebp				; set up the stack frame
	<+1>:	mov    ebp,esp
	<+3>:	cmp    DWORD PTR [ebp+0x8],0x3a2	; cmp 1786 with 930
	<+10>:	jg     0x512 <asm1+37>			; branch taken
	...
	<+37>:	cmp    DWORD PTR [ebp+0x8],0x6fa	; cmp 1786 with 1786
	<+44>:	jne    0x523 <asm1+54>			; branch not taken
	<+46>:	mov    eax,DWORD PTR [ebp+0x8]		; eax = 1786
	<+49>:	sub    eax,0x12				; eax = 1786 - 18 = 1768
	<+52>:	jmp    0x529 <asm1+60>			; unconditional jump
	...
	<+60>:	pop    ebp				; clean up stack frame
	<+61>:	ret   					; return 1768 (0x6e8)
```

**Flag**: 0x6e8
