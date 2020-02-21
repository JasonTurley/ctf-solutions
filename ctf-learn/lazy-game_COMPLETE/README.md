# Lazy Game Challenge

## Description

I found an interesting game made by some guy named "John_123". It is some betting game. I made some small fixes to the game; see if you can still pwn this and steal $1000000 from me!

To get flag, pwn the server at: ```nc thekidofarcrania.com 10001```


## Solution
In order to break the game, you need to enter a large negative value. I used
-$1000000.

Next, enter a guess larger than 10 until you get a game over. The server will
output the flag.
