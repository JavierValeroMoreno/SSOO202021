#!/bin/bash

ID=$(id -u)

if [ "$ID" != "0" ]; then
    TEMP=$PWD
    echo "Este script requiere de privilegios de root para leer /etc/shadow. Introduzca su contraseña" && su 
    "$TEMP/$0" -l;
fi
if [ "$ID" == "0" ]; then
    mkdir "/root/cuarentena"
    find / -name "*Hack*" -exec cp '{}' /root/cuarentena \;

fi