# dogcat
> I made a website where you can look at pictures of dogs and/or cats! Exploit a PHP
> application via LFI and break out of a docker container.

## Introduction

The challenge description states that there is a website vulnerable to local file
inclusion (LFI) that we need to exploit. Since it's running PHP, odds are we will need to 
upload a PHP reverse shell.

## Enumeration and Recon

Let's start with an nmap scan:
```
$ nmap -sV -T4 $IP

Starting Nmap 7.91 ( https://nmap.org ) at 2021-03-05 10:06 EST
Nmap scan report for 10.10.5.30
Host is up (0.24s latency).
Not shown: 998 closed ports
PORT   STATE SERVICE VERSION
22/tcp open  ssh     OpenSSH 7.6p1 Ubuntu 4ubuntu0.3 (Ubuntu Linux; protocol 2.0)
80/tcp open  http    Apache httpd 2.4.38 ((Debian))
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at
https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 29.99 seconds
```

This host has SSH enabled for remote login, and is running a HTTP web server. 

Navigate to the website:
![]

## Vulnerability


## Exploitation


## Privilege Escalation
