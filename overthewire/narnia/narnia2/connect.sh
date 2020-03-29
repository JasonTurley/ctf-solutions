#!/usr/bin/bash

sshpass -p $(cat ../narnia1/flag.txt) ssh narnia2@narnia.labs.overthewire.org -p 2226
