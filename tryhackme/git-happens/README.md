# Git Happens

## Enumeration
- http site on port 80
- found a /.git directory
- used git-dumper (stored in /opt/git-dumper) to download the remote repo to my
  machine

## The .git repo
Run ```git log``` to view history of commit messages.

Run the following command to view the source code pushed with each commit
```bash
git log | grep commit | cut -d " " -f2 | xargs git show
```

- git log: displays commit history and messages
- grep commit: display only the commit lines
- cut -d " " -f2: show just the commit hash number
- xargs git show: for each line, show the source code that was commited

## Solution
Run the previous command
Scroll to the bottom and you will find the username and password
