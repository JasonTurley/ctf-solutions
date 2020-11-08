
# Blue
Deploy & hack into a Windows machine, leveraging common misconfigurations issues.

## Task 1 - Recon
1. Scan the machine
```
No answer needed
```

2. How many ports are open with a port number under 1000?
```
3
```

3. What is this machine vulnerable to?
```
ms17-010
```

## Task 2 - Gain Access
1. Start Metasploit
```
No answer needed
```

2. Find the exploitation code we will run against the machine. What is the full
path of the code?
```
exploit/windows/smb/ms17_010_eternalblue
```

3. Show options and set the one required value. What is the name of this value?
```
RHOSTS
```

4. Run the exploit!
```
No answer needed
```

5. Confirm the exploit ran correctly.
```
No answer needed
```

## Task 3 - Escalate
1. How to convert normal shell to meterpreter:
```
post/multi/manage/shell_to_meterpreter
```
* I didn't use this method. Instead, I set the exploit payload as a meterpreter
* reverse_tcp shell.

2. Which option needs changing?
```
session
```

The rest of the questions for this section do not need answers.
2. Which option needs changing?
```
session
```

The rest of the questions for this section do not need answers.

## Task 4 - Cracking
1. What is the name of the non-default user?
```
Jon
```
* Note: run the hashdump command in meterpreter

2. What is his password?
```
alqfna22
```
* Note: ran
```
john john_hash --format=NT --wordlist=/usr/share/wordlists/rockyou.txt
```

## Task 5 - Find flags!
1. Flag1
```
{access_the_machine}
```
* Note: located in C:\ drive

2. Flag2
```

```

3. Flag3
```

```
