#!/bin/bash

sshpass -p $(cat ../narnia5/flag.txt) ssh narnia6@narnia.labs.overthewire.org -p 2226
