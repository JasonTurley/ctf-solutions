# Whats-the-difference

## Description
> Can you spot the difference? kitters cattos.

**Hints:**
- How do you find the difference between two files?
- Dumping the data from a hex editor may make it easier to compare.

**Points:** 200

## Solution
The two images are different. We can find the data that differs with the
cmp command!

```
$ cmp -b -l kitters.jpg cattos.jpg | awk '{ print $5 }' | tr -d "\n"; echo
picoCTF{th3yr3_a5_d1ff3r3nt_4s_bu773r_4nd_j311y_aslkjfdsalkfslkflkjdsfdszmz10548}
```

Explanation:
- cmp -b -l: compares two files and prints the bytes that differ
- awk '{ print $5 }': print only the 5th field (which has the flag)
- tr -d "\n": delete newline chars
- echo: print result with newline at end

## Lessons Learned/Pitfalls
- I was focused on using the command ```diff``` which finds the differences
  between text files. It doesn't work well for images.
- I used an online image comparing tool, but this did not reveal the flag.
- I learned about the command ```cmp``` - it's really neat!
