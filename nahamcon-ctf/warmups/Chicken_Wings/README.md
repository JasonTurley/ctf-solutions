# Chicken Wings

Download the chicken_wings file.

I always start these chicken_wingss by running the ```file``` command to see what
type of file I'm working with:

```
$ file chicken_wings
chicken_wings: UTF-8 Unicode text, with no line terminators
```

Next, check what is inside:

```
$ cat chicken_wings
i♐●♋♑❀♏📁🖮🖲📂♍♏⌛🖰♐🖮📂🖰📂🖰🖰♍📁🗏🖮🖰♌📂♍📁♋🗏♌♎♍🖲♏❝
```

What is this? Looks like we need to convert this to english. 

My first attempt was to decode the UTF-8 to ASCII, but this didn't lead to a
flag. I was stumped for a bit until I remembered that there is a font called
"Wingdings", which is similar to the chicken_wings title "Chicken Wings"

I found a Wingdings translator here:
[https://lingojam.com/WingdingsTranslator](https://lingojam.com/WingdingsTranslator)

Flag: flag{e0791ce68f718188c0378b1c0a3bdc9e}}
