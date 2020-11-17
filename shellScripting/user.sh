#!/bin/sh
echo "what's your name?"
read USER_NAME
echo "Hello $USER_NAME" #$ for the value of one variable
echo "I will create you a file called ${USER_NAME}_FILE"
# echo #${USER_NAME} curly brace to embed variable into a string
touch "${USER_NAME}_FILE"