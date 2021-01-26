#!/usr/bin/bash

grep "substring" index.html | sed 's/ //g' | sort | cut -d "'" -f 2
