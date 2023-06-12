#!/usr/bin/env sh

# Check the number of arguments
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

# Send SIGQUIT signal to the specified PID
kill -s QUIT "$1"
