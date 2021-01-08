# Ice
> Deploy & hack into a Windows machine, exploiting a very poorly secured media server.

## Recon 
I used nmap to scan the target IP:

```
nmap -sV -sC -Pn -oN nmap_initial $IP
```

nmap found a lot of open ports and services:


## Gain Access
From the nmap scan we see that the server is running a vulnerable version of Icecast. 
Icecast is a server for streaming audio and video. 


The exploit for this version of Icecast can be found on [CVE Details](https://www.cvedetails.com/cve/CVE-2004-1561/).

Set and run the exploit in msfconsole:


## Escalate Privileges


## Looting


## Post-Exploitation


## Extra Credit 
