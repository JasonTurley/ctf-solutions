# keygenme-py

## Details:
Category: Reverse Engineering

Points: 30

PicoCTF 2021

## Writeup

At the top of the provided keygenme-trial.py file we see the following data:

```python
username_trial = "FRASER"
bUsername_trial = b"FRASER"

key_part_static1_trial = "picoCTF{1n_7h3_|<3y_of_"
key_part_dynamic1_trial = "xxxxxxxx"
key_part_static2_trial = "}"
key_full_template_trial = key_part_static1_trial + key_part_dynamic1_trial + key_part_static2_trial
```

We see our given username (your's may be different) and three parts of the flag. We are interested
in the dynamic part.

After looking through the file, we notice a function that attempts to decrypt the user provided key:

```python
def check_key(key, username_trial):

    global key_full_template_trial

    if len(key) != len(key_full_template_trial):
        return False
    else:
        # Check static base key part --v
        i = 0
        for c in key_part_static1_trial:
            if key[i] != c:
                return False

            i += 1

        # TODO : test performance on toolbox container
        # Check dynamic part --v
        if key[i] != hashlib.sha256(username_trial).hexdigest()[4]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[5]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[3]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[6]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[2]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[7]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[1]:
            return False
        else:
            i += 1

        if key[i] != hashlib.sha256(username_trial).hexdigest()[8]:
            return False



        return True
```

I wrote the following script to determine the dynamic part:

```python
import hashlib
username_trial = b"FRASER"

# Static part of flag
flag = "picoCTF{1n_7h3_|<3y_of_"

# Decode dynamic part of flag
flag += hashlib.sha256(username_trial).hexdigest()[4]
flag += hashlib.sha256(username_trial).hexdigest()[5]
flag += hashlib.sha256(username_trial).hexdigest()[3]
flag += hashlib.sha256(username_trial).hexdigest()[6]
flag += hashlib.sha256(username_trial).hexdigest()[2]
flag += hashlib.sha256(username_trial).hexdigest()[7]
flag += hashlib.sha256(username_trial).hexdigest()[1]
flag += hashlib.sha256(username_trial).hexdigest()[8]

flag += "}"

print(flag)
```

picoCTF{1n_7h3_|<3y_of_ac73dc29}
