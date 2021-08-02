# Tomghost

## Initial Recon

To begin, scan the target IP address with nmap to determine open ports and
services:

```
$ nmap -sV 10.10.77.102
...
PORT     STATE SERVICE    VERSION
22/tcp   open  ssh        OpenSSH 7.2p2 Ubuntu 4ubuntu2.8 (Ubuntu Linux; protocol 2.0)
53/tcp   open  tcpwrapped
8009/tcp open  ajp13      Apache Jserv (Protocol v1.3)
8080/tcp open  http       Apache Tomcat 9.0.30
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel
```

Looks like the target is running an SSH server and two HTTP Apache webservers on
ports 8009 and 8080.
