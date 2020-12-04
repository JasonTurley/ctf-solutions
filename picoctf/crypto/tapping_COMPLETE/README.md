# Tapping

## Description
> There's tapping coming in from the wires. What's it saying
```
nc 2019shell1.picoctf.com 12285
```

**Hints:**
- What kind of encoding uses dashes and dots?
- The flag is in the format PICOCTF{}

## Solution
The netcat server gives us a sequence of morse code.

While possible to translate this by hand, I used this
[morse code translator](https://morsecode.world/international/translator.html) to get the
flag.
