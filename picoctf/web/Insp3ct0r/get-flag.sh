#!/usr/bin/bash
# The flag for this level is split amongst three webpages. I curl each of them and parse out the flag

curl --silent "https://jupiter.challenges.picoctf.org/problem/41511/{,mycss.css,myjs.js}" | grep flag | cut -d : -f 2 | awk '{print $1}' 
