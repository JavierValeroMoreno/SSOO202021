#!/bin/bash

if [ $# -eq 2 ]; then
	if ! [[ "$1$2" =~ ^[0-9]+$ ]]; then
		echo "$1$2"
		echo "Solo valores numericos"
	else
		sum=$(($1 + $2))
		echo "La suma de $1 y $2 es $sum"
	fi
else
	echo "No se han introduccido dos parametros numericos" 
fi
