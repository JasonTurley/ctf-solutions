# dont-trust-client-side

**Description:**

**Hint:**

**Points:** 100

## Source Code

Here's the source code for the index.html page:
```

```

It calls the JavaScript function ```verify()``` to check the password we enter
against the correct password. There's a bit of code obfuscation going on with the
```checkpass.substring()``` functions, but nothing we can't handle.


Essentially, the correct password is split at different locations to make reading
it a bit trickier. We could manually read the password flag, but it's much more fun
to write a script!

## Solution

Here's a janky bash script I wrote that (sort of) prints the flag:

```
#!/usr/bin/bash

grep "substring" index.html | sed 's/ //g' | sort | cut -d "'" -f 2
```

I used ```sed``` to strip the leading whitespace, and ```sort``` to roughly place the
flag pieces in the correct order.

And the output:
```
$ ./get-flag.sh  
pico
no_c
lien
ts_p
lz_1
a3c8
9}
CTF{
```

Reading the flag is much simpler now.

Flag: picoCTF{no_clients_plz_1_a3c89}
