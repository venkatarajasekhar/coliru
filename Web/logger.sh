#!/bin/bash

# Kill previous instance of _logger.sh (if any)
ps -eopid,comm | grep '_logger.sh' | grep -v grep | awk '{print $1}' | while read line;  do
     echo "Killing previous instance $line"
     kill -9 $line
done

rm -f .stdout
mkfifo .stdout
chown webserver:coliru .stdout

while true ; do
    ./_logger.sh 
done & disown
