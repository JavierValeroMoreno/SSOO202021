#!/bin/bash

echo "Introduzca el primer valor"
read val1

echo "Introduzca el segundo valor"
read val2

echo "Introduzca el tercer valor"
read val3

if ! [[ "$val1$val2$val3" =~ ^[0-9]+$ ]]; then
	echo "No se han introducido valores numericos"
else
	sum=$(( $val1 + $val2 + $val3 ))
	mult=$(( $val1 * $val2 * $val3 ))
	echo "La suma de $val1, $val2 y $val3 es $sum y su multiplicacion $mult"
fi
