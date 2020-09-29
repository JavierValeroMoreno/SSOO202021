#!bin/bash

ID=$(id -u)

if [ "$ID" != "0"] then

    TEMP=$PWD
    echo "Este script requiere de privilegios de root para leer /etc/shadow. Introduzca su contraseña" && su -c
    "$TEMP/$0" -l
fi
if [ "$ID" == "0"] then
    echo "Mostramos /etc/passwd"
    cat /etc/passwd
    echo "Pulse enter para continuar"
    read enter
    echo "Mostramos /etc/shadow"
    cat /etc/shadow
fi