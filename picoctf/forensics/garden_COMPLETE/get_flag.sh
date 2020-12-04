#!/usr/bin/bash

../../shell.sh 'cd /problems/glory-of-the-garden_0_25ece79ae00914856938a4b19d0e31af; strings garden.jpg | grep picoCTF | cut -d " " -f 5 | tr -d "\""'
