# Anthem

## Enumeration

Starting off with an nmap scan on the IP address:

```console
$ nmap -sV 10.10.153.139 -oN nmap_scan
Starting Nmap 7.91 ( https://nmap.org ) at 2021-05-12 15:29 EDT
Nmap scan report for 10.10.153.139
Host is up (0.21s latency).
Not shown: 998 filtered ports
PORT     STATE SERVICE       VERSION
80/tcp   open  http          Microsoft HTTPAPI httpd 2.0 (SSDP/UPnP)
3389/tcp open  ms-wbt-server Microsoft Terminal Services
Service Info: OS: Windows; CPE: cpe:/o:microsoft:windows

Service detection performed. Please report any incorrect results at
https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 46.05 seconds
```

We see that there is a web server running on port 80, and a Remote Desktop
service on port 3389.

Let's now navigate to the website.

![landing page](./screenshots/landing.png)

We are greeted with the site title and a couple of blog posts. Check out
robots.txt for the possible password:

![robots](./screenshots/robots.txt)

### Finding the Administrator name

The second blog post on the page contains a nursery ryhme. Googling it returns
the name of the author, and admin for this site, Solomon Grundy.



After running gobuster, I found the hidden directory /install, which redirects
to a login panel.  
