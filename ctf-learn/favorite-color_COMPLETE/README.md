# Favorite Color
What's your favorite color? Would you like to share with me? Run the command: ssh color@104.131.79.111 -p 1001 (pw: guest) to tell me!

## Solution
After connecting to the server, examine the ```color.c``` source code. The gets() function is vulnerable and can
be exploited with a buffer overflow. Overwrite 52 bytes (32B buffer + 16B of padding + 4B ebp) to gain control
of the eip. Next, write a stack address to jump to. In this case, I jumped into the if conditional and executed a shell.

