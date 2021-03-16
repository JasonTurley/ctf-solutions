# Buzz

Buzz is a warmup challenge worth 50 points.

To begin, I ran the ```file``` command:

```
$ file buzz  
buzz: compress'd data 16 bits
```

The *compress'd* in the output of the ```file``` command is not a typo. It is
the name of a Unix program used to compress files. 

If you are using a Debian-based Linux distro (like Kali Linux), use the
```uncompress.real``` program. For anything else, use ```uncompress```.

```
$ uncompress.real -c buzz	# -c prints to stdout
flag{b3a33db7ba04c4c9052ea06d9ff17869}
```
