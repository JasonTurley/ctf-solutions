#!/usr/bin/env python

import sys

if len(sys.argv) < 2:
    print('Usage: python3 script.py <mode> <numbers>')
    exit()

for i in range(2, len(sys.argv)):
    mode = int(sys.argv[1])

    print(chr(int(sys.argv[i], mode)), end="")

print('')
