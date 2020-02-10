#!/bin/sh

if grep -Fqvf $1 $2; then
    echo "There are lines in $1 that don’t occur in $2."
else
	echo "All lines in $1 are in $2"
fi