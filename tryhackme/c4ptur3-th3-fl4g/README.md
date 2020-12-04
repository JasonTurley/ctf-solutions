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

The text is encrypted with ROT47. CyberChef to the rescue:
You spin me right round baby right round (47 times)

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

10. Super long text

This problem is encrypted multiple times with ciphers we have used in previous tasks. I entered the following CyberChef recipes in this order:

- From Base64
- From Morse Code
- From Binary
- ROT47
- From Decimal

```
Let's make this a bit trickier...
```

## Spectograms
> A spectrogram is a visual representation of the spectrum of frequencies of a signal as it varies with time. When applied to an audio signal, spectrograms are sometimes called sonographs, voiceprints, or voicegrams. When the data is represented in a 3D plot they may be called waterfalls. 

Here are the steps I followed to get this flag:
- download file
- open file in Audacity
- click dropdown menu
- select "spectogram" to reveal flag

TODO: add photos of soundwaves and flag

## Steganography
> Steganography is the practice of concealing a file, message, image, or video within another file, message, image, or video.

1. Decode the image to reveal the answer.

First I used steghide to inspect the downloaded JPG file:

```
$ steghide info stegosteg.jpg 
"stegosteg.jpg":
  format: jpeg
  capacity: 2.5 KB
Try to get information about embedded data ? (y/n) y
Enter passphrase: 
  embedded file "steganopayload2248.txt":
    size: 13.0 Byte
    encrypted: rijndael-128, cbc
    compressed: yes
```

We see that there is an embedded text file! Time to extract it:

```
$ steghide extract -sf stegosteg.jpg
Enter passphrase: 
wrote extracted data to "steganopayload2248.txt".
                                                                                                                  
$ cat steganopayload2248.txt 
SpaghettiSteg
```

## Security through obscurity
> Security through obscurity is the reliance in security engineering on the secrecy of the design or implementation as the main method of providing security for a system or component of a system.

1. Download and get 'inside' the file. What is the first filename & extension?

```

```

2. Get inside the archive and inspect the file carefully. Find the hidden text.

Both answers can be found by running the strings command on the file:
```
$ strings -7 meme.jpg
+VaTH;O(
i1M/W~a
r;%l@k4
"AHH_YOU_FOUND_ME!" 
hackerchat.png
```
