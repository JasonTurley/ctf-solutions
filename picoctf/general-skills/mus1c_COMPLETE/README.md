# mus1c

## Description
> I wrote you a song. Put it in the picoCTF{} flag format

**Hints:**
- Do you think you can master rockstar?

**Points:** 300

## Solution
The lyrics.txt is written in the [Rockstar](https://codewithrockstar.com/online) programming language. Running
the code through the rockstar [online compiler](https://codewithrockstar.com/online),
we get the following results:

```
114
114
114
111
99
107
110
114
110
48
49
49
49
114
```

This is ascii! Let's decode in python:

```
>>> ascii = "114 114 114 111 99 107 110 114 110 48 49 49 51 114"
>>> for c in ascii.split():
...     print(chr(int(c)), end ='')
...
...
rrrocknrn0113r
>>>
```

The flag is ```picoCTF{rrrocknrn0113r}```
