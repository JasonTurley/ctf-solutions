# Insp3ct0r
**Description**: Kishor Balan tipped us off that the following code may need inspection: https://jupiter.challenges.picoctf.org/problem/41511/ or [link](https://jupiter.challenges.picoctf.org/problem/41511/)

**Hints**
- How do you inspect web code on a browser?
- There's 3 parts

## Solution

One way to solve this challenge is by inspecting the source code of the three sites: index.html, mycss.css, and 
myjs.js. This can be done by pressing Ctrl+Shift+I or Ctrl+U in the web browser.
The flag is divided into three parts in the comments of each page.

An alternate, more fun solution is to write a bash script to do this automatically :)

Here's the source code for the script I wrote:
```
#!/usr/bin/bash
# The flag for this level is split amongst three webpages. I curl each of them and parse out the flag

curl --silent "https://jupiter.challenges.picoctf.org/problem/41511/{,mycss.css,myjs.js}" | grep flag | cut -d : -f 2 | awk '{print $1}'
```

And here's the script in action:
```
$ ./get-flag.sh 
picoCTF{tru3_d3
t3ct1ve_0r_ju5t
_lucky?832b0699}
```

Maybe in the future I'll clean it up so the text is all on one line...
