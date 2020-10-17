# Lian_Yu

Objective is to find the user and root flags.
*Welcome to Lian_YU, this Arrowverse themed beginner CTF box! Capture the flags
and have fun.*

1. Deploy the VM and start enumeration
```
nmap -sV -sC -Pn -oN nmap/initial $IP
```

2. What is the Web Directory you found?
```
root@ip-10-10-93-241:~# gobuster dir -u http://$IP/island/ -w
4-digits-0000-9999.txt
===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://10.10.97.166/island/
[+] Threads:        10
[+] Wordlist:       4-digits-0000-9999.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/09/30 17:11:40 Starting gobuster
===============================================================
/2100 (Status: 301)
===============================================================
2020/09/30 17:11:41 Finished
===============================================================
```


```
Answer: 2100
```

https://raw.githubusercontent.com/danielmiessler/SecLists/master/Fuzzing/4-digits-0000-9999.txt

3. what is the file name you found?

4. what is the FTP Password?


5. what is the file name with SSH password?


6. user.txt

7. root.txt


## Notes

- Find a way to **Lian_Yu** The code word is: vigilante
- found http://$IP/island/ web directory

## What I learned
- Fuzz everything! I did not think to fuzz the /island directory!
