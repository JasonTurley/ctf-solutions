# esab64

A warmup challenge for 50 points

> Was it a car or a cat I saw? 

This was a cute challenge. Download the file and open it:

```
$ cat esab64            
mxWYntnZiVjMxEjY0kDOhZWZ4cjYxIGZwQmY2ATMxEzNlFjNl13X
```

I then piped the output into base64 to try to decode it:
```
$ cat esab64 | base64 -d      
XH@΅ā   LX]
```

It didn't work! Hmmm, the title of this challenge is esab64, which is base64 in
reverse.

Aha! That's a hint to reverse the text and then decode it! 

```
$ rev esab64 | base64 -d      
_}e61e711106bd0db1b78efa894b1125bf{galf
```

Close. One more reverse should do it.

```
$ rev esab64 | base64 -d | rev
flag{fb5211b498afe87b1bd0db601117e16e}_
```


