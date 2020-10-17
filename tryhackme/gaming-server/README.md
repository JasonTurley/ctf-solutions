# GamingServer
**Description:** An Easy Boot2Root box for beginners.

## Task 1 - Boot2Root
Can you gain access to this gaming server built by amateurs with no experience
of web development and take advantage of the deployment system.


1. What is the user flag?


2. What is the root flag?


### nmap
```
nmap -sV -sC -Pn $IP

PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol
2.0)
| ssh-hostkey:
|   2048 34:0e:fe:06:12:67:3e:a4:eb:ab:7a:c4:81:6d:fe:a9 (RSA)
|   256 49:61:1e:f4:52:6e:7b:29:98:db:30:2d:16:ed:f4:8b (ECDSA)
|_  256 b8:60:c4:5b:b7:b2:d0:23:a0:c7:56:59:5c:63:1e:c4 (EdDSA)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
| http-methods:
|_  Supported Methods: POST OPTIONS HEAD GET
|_http-server-header: Apache/2.4.29 (Ubuntu)
|_http-title: House of danak
MAC Address: 02:59:CE:37:01:BB (Unknown)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

* ssh and http webserver

### website enumeration
* found possible user john in comments of landing page
* gobuster results:
```
root@ip-10-10-90-251:~# gobuster dir -w
/usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u http://$IP:80
===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://10.10.28.111:80
[+] Threads:        10
[+] Wordlist:       /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/10/17 01:13:24 Starting gobuster
===============================================================
/uploads (Status: 301)
/secret (Status: 301)
/server-status (Status: 403)
===============================================================
2020/10/17 01:13:46 Finished
===============================================================
```

### Notes
* found list of possible passwords in /uploads
* tried to brute force login with hydra (failed)
* found private RSA key in /secret, it is passphrase protected
* downloaded ssh2john.py to convert the RSA key into a hash for john
* used john to crack the hash
```
john --wordlist=./dict.lst for_john.txt
```
* ssh'd into the server and the user flag is in the home directory
* looking for priv esc commands
    * ```find / -perm -u=s -type f 2>/dev/null``` --> found /usr/bin/pkexec
	* cannot use it without knowing john's password
    * linpeas

