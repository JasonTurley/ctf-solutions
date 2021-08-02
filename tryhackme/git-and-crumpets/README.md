

## Initial Recon

Grab the IP address and scan it with nmap to find open ports and services.

```
$ nmap -sV -Pn 10.10.236.87
PORT   STATE SERVICE VERSION
80/tcp open  http    nginx
```

Looks like the only service is an HTTP server on port 80. 

Entering the IP into a web browser redirects yields a Rick Roll :/

Let's see what happens when we curl the site:

```
$ curl http://10.10.236.87
```

We get a ton on text. Notice the note towards the top:

```
<p> 
	Hey guys,
           I set up the dev repos at git.git-and-crumpets.thm, but I haven't
	   gotten around to setting up the DNS yet. 
           In the meantime, here's a fun video I found!
        Hydra
</p>
``` 

Two important things here:
1. A hidden domain: **git.git-and-crumpets.thm**
2. A username "Hydra" 


...

- Add git.git-and-crumpets.thm to /etc/hosts
- Create a username and password
- Explore the 2 repos
- Scones cant touch this repo
   - Clone and run git log
   - password is in avatar
- Download JPG and run strings

$ strings avatar.jpg| grep -i password
My 'Password' should be easy enough to guess

Username: scones
Password: Password
