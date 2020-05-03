#!/usr/bin/bash

sshpass -p $(cat ../narnia3/flag.txt) ssh narnia4@narnia.labs.overthewire.org -p 2226
