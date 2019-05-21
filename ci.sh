#!/bin/sh

command -v entr
if [ $? != 0 ]; then
	echo "Can not found entr utility, please install it before trying again"
	exit 1
fi

ls src/* | entr -cr ./test.sh
