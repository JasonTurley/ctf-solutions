# Ninja Skills

![ninja](https://i.imgur.com/HNs4Vov.png)

[Ninja Skills](https://tryhackme.com/room/ninjaskills) is a [TryHackMe](https://tryhackme.com) room for improving Linux command line skills. Note that all answers have been redacted from this writeup.

We are tasked with answering a set of questions about the following files:

- 8V2L
- bny0
- c4ZX
- D8B3
- FHl1
- oiMO
- PFbD
- rmfX
- SRSq
- uqyw
- v2Vb
- X1Uy

The goal is to solve the challenges as efficiently as possible. Most of the challenges can be solved with some form of

```
find / -name <filename>  -exec <command> \;
```

To keep track of the target files, I added them to a text file:

```
$ cat filenames
8V2L
bny0
c4ZX
D8B3
FHl1
oiMO
PFbD
rmfX
SRSq
uqyw
v2Vb
X1Uy
```

Now I can use a for loop to run a command against each file! The basic syntax for this is:

```
for i in $(cat filenames); do find / -name "$i"  -exec <command> \; 2>/dev/null; done
```

## Challenge Questions

### Challenge 1: Which of the above files are owned by the best-group group?

Use the `-group <groupname>` switch to find all files owned by a specific group:

```
$ find / -group best-group  2>/dev/null
```

### Challenge 2: Which of these files contain an IP address?

We can use [grep to find an IP address in a file](https://www.putorius.net/grep-an-ip-address-from-a-file.html).

```
grep -Eo '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}'
```

Now, add it to the find command:

```
$ for i in $(cat filenames); do find / -name "$i" -exec grep -E -o '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' '{}' \; 2>/dev/null; done
1.1.1.1
```

Sweet, it works! To print the filename, change the `-o` to a `-l`

```
$ for i in $(cat filenames); do find / -name "$i" -exec grep -E -l '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' '{}' \; 2>/dev/null; done
```

### Challenge 3: Which file has the SHA1 hash of 9d54da7584015647ba052173b84d45e8007eba94

Add `-exec sha1sum '{}' \;` to our `find` command in order to take the sha1sum of each file!

```
$ for i in $(cat filenames); do find / -name "$i"  -exec sha1sum '{}' \; 2>/dev/null; done | grep 9d54
```

### Challenge 4: Which file contains 230 lines?

Add `-exec wc -l '{}' \;` to the `find` command:

```
$ for i in $(cat filenames); do find / -name "$i"  -exec wc -l '{}' \; 2>/dev/null; done 
209 /etc/8V2L
209 /mnt/c4ZX
209 /mnt/D8B3
209 /var/FHl1
209 /opt/oiMO
209 /opt/PFbD
209 /media/rmfX
209 /etc/ssh/SRSq
209 /var/log/uqyw
209 /home/v2Vb
209 /X1Uy
```

The file that is missing is the answer to the question.

### Challenge 5: Which file's owner has an ID of 502?

View file ownership by adding `-exec ls -la '{}' \;`. 

In the below output, there is one file owner who is not our current user.

```
$ for i in $(cat filenames); do find / -name "$i"  -exec ls -la '{}' \; 2>/dev/null; done 
-rwxrwxr-x 1 new-user new-user 13545 Oct 23  2019 /etc/8V2L
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /mnt/c4ZX
-rw-rw-r-- 1 new-user best-group 13545 Oct 23  2019 /mnt/D8B3
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /var/FHl1
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /opt/oiMO
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /opt/PFbD
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /media/rmfX
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /etc/ssh/SRSq
-rw-rw-r-- 1 new-user new-user 13545 Oct 23  2019 /var/log/uqyw
-rw-rw-r-- 1 new-user best-group 13545 Oct 23  2019 /home/v2Vb
-rw-rw-r-- 1 newer-user new-user 13545 Oct 23  2019 /X1Uy
```

There is one unique file owner. Run `id <user>` to get their UID.

### Challenge 6: Which file is executable by everyone?

The `-executable` switch displays files that are marked as executable:

```
$ for i in $(cat filenames); do find / -name "$i" -executable 2>/dev/null; done 
```
