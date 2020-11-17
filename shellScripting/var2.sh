#!/bin/sh
echo "MYVAR IS $MYVAR"
MYVAR="hi there"
echo "MYVAR IS $MYVAR"
#source a scipt wia the "."(dot) command, to receive variables changes from
#the scipt
#this export is not required, dot means force scipt runing within our own 
#interactive shell