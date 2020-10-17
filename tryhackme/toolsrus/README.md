# ToolsRus
Your challenge is to use the tools listed below to enumerate a server, gathering
information along the way that will eventually lead to you taking over the
machine.


This task requires you to use the following tools:
- Dirbuster
- Hydra
- Nmap
- Nikto
- Metasploit

## Notes

### Nmap
Tasks 5,6,8,and 9 can be solved with the following nmap scan:
```
nmap -sV -sC -Pn -oN nmap_scan $IP
```

### Gobuster
I chose to use gobuster instead of dirbuster here.

===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://10.10.155.36:80
[+] Threads:        10
[+] Wordlist:       /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/10/16 16:47:28 Starting gobuster
===============================================================
/guidelines (Status: 301)
/protected (Status: 401)
/server-status (Status: 403)
===============================================================
2020/10/16 16:47:49 Finished
===============================================================


## Hydra
Run the following command to get the password for the protected directory:
```
hydra -l bob -P /usr/share/wordlists/rockyou.txt $IP http-get -m http://$IP/protected
```

## Tasks
1. What directory can you find, that begins with a "g"?


2. Whose name can you find from this directory?


3. What directory has basic authentication?


4. What is bob's password to the protected part of the website?


5. What other port that serves a webs service is open on the machine?


6. Going to the service running on that port, what is the name and version of
the software?

Answer format: Full_name_of_service/Version



7. Use Nikto with the credentials you have found and scan the /manager/html
directory on the port found above.

How many documentation files did Nikto identify?


8. What is the server version (run the scan against port 80)?


9. What version of Apache-Coyote is this service using?


10. Use Metasploit to exploit the service and get a shell on the system.

What user did you get a shell as?



11. What text is in the file /root/flag.txt



