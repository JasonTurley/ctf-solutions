## new-overflow-1

Simple buffer overflow exploit. The main difference is that this is a 64-bit
system.

Write 64 bytes to fill buffer + 8 bytes to overwrite rbp + the flag() address.

This works, but fopen() in the flag() fails to open flag.txt.
