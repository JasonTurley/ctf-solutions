# Overflow 2

## Description
Now try overwriting arguments. Can you get the flag from this program? You can find it in /problems/overflow-2_5_4db6d300831e973c59360066ec1cf0a4 on the shell server. Source.

**Hints:** GDB can print the stack after you send arguments.

## Solution
* First overflow the buffer and ebp with garbage data.
* Next, overwrite the eip to point to the flag function.
* Add 4 bytes of fluff then insert the correct parameters to get the flag.
