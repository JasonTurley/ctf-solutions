# c4ptur3-th3-fl4g
> A beginner level CTF challenge

## Translating & Shifting
> Translate, shift and decode the following;
> Answers are all case sensitive.

1. c4n y0u c4p7u23 7h3 f149?
**Answer:** can you capture the flag?

2. 01101100 01100101 01110100 01110011 00100000 01110100 01110010 01111001 00100000 01110011 01101111 01101101 01100101 00100000 01100010 01101001 01101110 01100001 01110010 01111001 00100000 01101111 01110101 01110100 00100001

I entered the data into a [binary to text translator website from RapidTables](https://www.rapidtables.com/convert/number/binary-to-ascii.html).

lets try some binary out!

3. MJQXGZJTGIQGS4ZAON2XAZLSEBRW63LNN5XCA2LOEBBVIRRHOM======

```
echo "MJQXGZJTGIQGS4ZAON2XAZLSEBRW63LNN5XCA2LOEBBVIRRHOM======" > challenge3.txt
base32 -d challenge3.txt 
base32 is super common in CTF's
```

4. RWFjaCBCYXNlNjQgZGlnaXQgcmVwcmVzZW50cyBleGFjdGx5IDYgYml0cyBvZiBkYXRhLg==

```
echo "RWFjaCBCYXNlNjQgZGlnaXQgcmVwcmVzZW50cyBleGFjdGx5IDYgYml0cyBvZiBkYXRhLg==" > challenge4.txt
base64 -d challenge4.txt
Each Base64 digit represents exactly 6 bits of data.
```

5. 68 65 78 61 64 65 63 69 6d 61 6c 20 6f 72 20 62 61 73 65 31 36 3f
 
I wrote a short Python script to translate the hex to ascii characters:

```
# Translates the hex characters to ascii

hex = "68 65 78 61 64 65 63 69 6d 61 6c 20 6f 72 20 62 61 73 65 31 36 3f".split()

for h in hex:
        print(chr(int(h, 16)), end="")

print()
```

hexadecimal or base16?

6. Ebgngr zr 13 cynprf!

This is encrypted with [ROT13](https://en.wikipedia.org/wiki/ROT13) substitution cipher. I cracked it on CyberChef. 

Rotate me 13 places!


7. *@F DA:? >6 C:89E C@F?5 323J C:89E C@F?5 Wcf E:>6DX* 

8. - . .-.. . -.-. --- -- -- ..- -. .. -.-. .- - .. --- -.

. -. -.-. --- -.. .. -. --.

CyberChef has a recipe for cracking morse code

TELECOMMUNICATION  ENCODING 

9. 85 110 112 97 99 107 32 116 104 105 115 32 66 67 68


I wrote a small Python script to translate the decimal to ascii characters:

```
# Translates decimal cdaracters to ascii

decimal = "85 110 112 97 99 107 32 116 104 105 115 32 66 67 68".split()

for d in decimal:
        print(chr(int(d, 10)), end="")

print()
```
