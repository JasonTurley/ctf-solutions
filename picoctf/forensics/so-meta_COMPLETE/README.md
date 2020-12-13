# So Meta
> Find the flag in this picture.

**Points:** 150

**Hints**:
1. What does meta mean in the context of files?
2. Ever heard of metadata?

## Solution
The flag can be found with the ```strings``` command.

```
$ strings -10 pico_img.png
...
...
picoCTF{s0_m3ta_fec06741}}
```
