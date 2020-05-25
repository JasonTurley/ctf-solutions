# Learn Linux

```
export IP=10.10.10.204
```

## Binary - Shiba1
1. What's the password for shiba2?
```
pinguftw
```

## Binary - Shiba2
1. What's the password for shiba3?
```
happynootnoises
```

## Binary - Shiba3
1. What's the password for shiba4?
```
test1234
```

## Bonus challenge!
Read the flag stored at /root/root.txt that is owned by root.

This one was quite challenging! Here a a few failed brainstorming ideas I though
of:

- crack root password (not taught in room)
- add user to /etc/sudoers (nope, permission denied)
- read /etc/sudoers to see which user has root privilege
- chown (permission denied)
- chmod (permission denied)
- ln or ln -s (did not work, permission denied)

Running the following command revealed an interesting file
```
find / -user shiba2 -type f 2>>/dev/null

/var/log/test1234
```

This file contains the following username and password!
```
nootnoot:notsofast
```

su to nootnoot and cat /root/root.txt
```
ad91979868d06e19d8e8a9c28be56e0c
```
