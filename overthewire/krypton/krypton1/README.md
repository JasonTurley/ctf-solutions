# krypton1
> The password for level 2 is in the file ‘krypton2’. It is ‘encrypted’ using a
> simple rotation. It is also in non-standard ciphertext format. When using alpha
> characters for cipher text it is normal to group the letters into 5 letter
> clusters, regardless of word boundaries. This helps obfuscate any patterns.
> This file has kept the plain text word boundaries and carried them to the
> cipher text. Enjoy!


This challenge uses ROT13 to encode the password.

Use bash build in ```tr``` to decode:
```
cat krypton2 | tr 'A-Za-z' 'N-ZA-Mn-za-m'
```

Outputs "LEVEL TWO PASSWORD ROTTEN"

Flag:
```
ROTTEN
```
