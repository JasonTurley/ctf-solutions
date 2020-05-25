# krypton2
> The password for level 3 is in the file krypton3. It is in 5 letter group
> ciphertext. It is encrypted with a Caesar Cipher. Without any further
> information, this cipher text may be difficult to break. You do not have
> direct access to the key, however you do have access to a program that will
> encrypt anything you wish to give it using the key. If you think logically,
> this is completely easy.

Generated alphabet file with command:
```
echo {a..z} {A..Z} | tr -d [:space:] > alphabet
```

Encrypted with:
```
./encrypt alphabet
MNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKL
```

Manually decoded the caesar cipher.

Flag:
```
caesariseasy
```
