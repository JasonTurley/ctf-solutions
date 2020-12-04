## la cifra de

**View full writeup:** https://jasonturley.xyz/picoctf-2019-la-cifra-de-writeup/

## Description
> I found this cipher in an old book. Can you figure out what it says? Connect
> with ```nc 2019shell1.picoctf.com 61559```

**Hints:**
- There are tools that make this easy.
- Perhaps looking at history will help

**Points:** 200

## Solution
The netcat server gives us an encrypted message. I went to
[Cyber Chef](https://gchq.github.io/CyberChef/) and searched for a decoder.

Since the title of this challenge is in French, I chose a French titled decoder:
the *Vigenere cipher*. This decoder requires a key. After several minutes of
guessing, I found that the correct key is "flag".

Enter this to decode the message and get the flag.

## Lessons Learned
- Learned about the [Vigenere
  Cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#:~:text=The%20Vigen%C3%A8re%20cipher%20(French%20pronunciation,a%20form%20of%20polyalphabetic%20substitution.)
