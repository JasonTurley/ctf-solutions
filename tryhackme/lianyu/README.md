# Lian Yu

## Task 1 - Enumeration

### nmap

root@ip-10-10-113-29:~# nmap -sV -sC -Pn -oN nmap/initial $IP

Starting Nmap 7.60 ( https://nmap.org ) at 2020-10-14 01:07 BST
Nmap scan report for ip-10-10-18-144.eu-west-1.compute.internal (10.10.18.144)
Host is up (0.0011s latency).
Not shown: 996 closed ports
PORT    STATE SERVICE VERSION
21/tcp  open  ftp     vsftpd 3.0.2
22/tcp  open  ssh     OpenSSH 6.7p1 Debian 5+deb8u8 (protocol 2.0)
| ssh-hostkey: 
|   1024 56:50:bd:11:ef:d4:ac:56:32:c3:ee:73:3e:de:87:f4 (DSA)
|   2048 39:6f:3a:9c:b6:2d:ad:0c:d8:6d:be:77:13:07:25:d6 (RSA)
|   256 a6:69:96:d7:6d:61:27:96:7e:bb:9f:83:60:1b:52:12 (ECDSA)
|_  256 3f:43:76:75:a8:5a:a6:cd:33:b0:66:42:04:91:fe:a0 (EdDSA)
80/tcp  open  http    Apache httpd
|_http-server-header: Apache
|_http-title: Purgatory
111/tcp open  rpcbind 2-4 (RPC #100000)
| rpcinfo: 
|   program version   port/proto  service
|   100000  2,3,4        111/tcp  rpcbind
|   100000  2,3,4        111/udp  rpcbind
|   100024  1          41088/udp  status
|_  100024  1          42262/tcp  status
MAC Address: 02:A8:B6:F6:60:19 (Unknown)
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 9.31 seconds
root@ip-10-10-113-29:~# 

Open services:
- ssh
- http
- rpcbind


### gobuster
root@ip-10-10-113-29:~# gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://$IP
===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://10.10.18.144
[+] Threads:        10
[+] Wordlist:       /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/10/14 01:09:23 Starting gobuster
===============================================================
/island (Status: 301)
/server-status (Status: 403)
===============================================================
2020/10/14 01:09:40 Finished
===============================================================
root@ip-10-10-113-29:~# 


### /island webpage
Highlighting the webpage (or viewing the source) reveals codname *vigilante*. Perhaps this is a username for later??

## Task 2 - what is the Web Directory you found
```
2100
```

gobuster dir -w /usr/share/wordlists/SecLists/Fuzzing/4-digits-0000-9999.txt -u http://$IP/island
===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://10.10.18.144/island
[+] Threads:        10
[+] Wordlist:       /usr/share/wordlists/SecLists/Fuzzing/4-digits-0000-9999.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/10/14 01:14:58 Starting gobuster
===============================================================
/2100 (Status: 301)
===============================================================
2020/10/14 01:14:59 Finished
===============================================================
root@ip-10-10-113-29:~#


```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://$IP/island/2100/ -x .ticket
```

## Task 3 - what is the file name you found?
```
green_arrow.ticket
```

## Task 4 - what is the FTP password
Navigate to the above URL and find the encoded string. Run it through Cyber Chef base58 decoder to get the FTP password!

 ----
 On the FTP server download all images.

 Change the file header of Leave_me_along.png to the one below:

00000000: 8950 4e47 0d0a 1a0a 0000 000d 4948 4452  .PNG........IHDR

Open Leave_me_alone.png to get the password *password*. Next, examine the aa.jpg with steghide:
```
steghide extract -sf aa.jpg
password:
```

## Task 5 - What is the file name with SSH password?
```
shado
```

The password is *M3tahuman*

Now we need a username. I tried vigilante and shado, but neither worked. I checked the FTP server again, ran ```cd ..``` and the ```ls``` and found another user.

SSH into the machine with that found username and password

## Task 6 - user.txt
The user.txt file is in the initial home directory. Print the flag with ```cat user.txt```


## Task 7 - root.txt
I ran sudo -l to see what, if any, commands I could run as sudo. Turns out this user can run pkexec, which allows them to run a command as another user! 


This means we can run commands as root. Print out /root/root.txt to get the flag.