#!/bin/bash

sshpass -p $(cat ../narnia4/flag.txt) ssh narnia5@narnia.labs.overthewire.org -p 2226
