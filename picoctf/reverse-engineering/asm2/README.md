# asm2

## Description
> What does asm2(0x4,0x21) return? Submit the flag as a hexadecimal value
> (starting with '0x'). NOTE: Your submission for this question will NOT be in
> the normal flag format.

**Points:** 250

## Source Code
I added my own comments:

```
# asm2(0x4, 0x21) --> asm2(4, 33)

asm2:
	<+0>:	push   ebp				; set up stack frame
	<+1>:	mov    ebp,esp
	<+3>:	sub    esp,0x10				; alloc local variables
	var1 and var2
	<+6>:	mov    eax,DWORD PTR [ebp+0xc]		; eax  = 33
	<+9>:	mov    DWORD PTR [ebp-0x4],eax		; var1 = 33
	<+12>:	mov    eax,DWORD PTR [ebp+0x8]		; eax  = 4
	<+15>:	mov    DWORD PTR [ebp-0x8],eax		; var2 = 4
	<+18>:	jmp    0x509 <asm2+28>			; unconditional jump
	<+20>:	add    DWORD PTR [ebp-0x4],0x1		; var1 += 1
	<+24>:	add    DWORD PTR [ebp-0x8],0x74		; var2 += 116
	<+28>:	cmp    DWORD PTR [ebp-0x8],0xfb46	; cmp 4 with 64326
	<+35>:	jle    0x501 <asm2+20>			; branch taken
	<+37>:	mov    eax,DWORD PTR [ebp-0x4]		; eax = var1
	<+40>:	leave					; clean up stack frame
	<+41>:	ret
```

## Solution

Two local variables are created and initialized to the function parameters.

The two variables are incremented in a loop until var2 is greater than 0xfb46
(64326). var1 is incremented by 1 and var2 is incremented by 116.

Some quick math shows us that 64326 / 116 = 554. Add 1 to this for the initial
loop check to get a total of 555 loop iterations.

So var1 (which was initially 33) is now 33 + (1 * 555) = 588 --> 0x24c

**Flag:** 0x24c
