# Petshop Pro

Web CTF challenge from https://ctf.hacker101.com/ctf

## Flag 0

- "Add to Cart" any number of kittens or puppies. 
- Proceed to checkout
- In Burp or Dev Tools, edit the price to $0
- The flag should be generated in the response

## Flag 1

- Scan the IP address with a directory enumeration tool (i.e gobuster)
- Found login page
- Enter "admin:admin" get Incorrect Username
- Guess usernames until "Incorrect Username" error code is gone
- Tried these wordlists:
	- /usr/share/wordlists/metasploit/mirai_user.txt
	- /usr/share/wordlists/metasploit/default_users_for_services_unhash.txt
	- This wordlist worked! https://github.com/jeanphorn/wordlist/blob/master/usernames.txt

`$ hydra -f -L ./usernames.txt -p test 35.190.155.168 http-form-post
"/f6e630520d/login:username=^USER^&password=^PASS^:Invalid username"`

- Username: annora

`$ hydra -f -l annora -P /usr/share/wordlists/rockyou.txt 35.190.155.168
http-form-post "/f6e630520d/login:username=^USER^&password=^PASS^:Invalid
password"`

- Password: kerry

Once you login, the flag is visible on the main page

## Flag 2

- Edit the Kitten data
- Add basic XSS alert(1) for name
- Goto cart
- Flag is visible
