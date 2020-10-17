#!/bin/bash

ID=$(id -u)

if [ "$ID" != "0" ]; then

    TEMP=$PWD
    echo "Este script requiere de privilegios de root para leer /etc/shadow"
fi
if [ "$ID" == "0" ]; then
    echo "Mostramos /etc/passwd"
    sh -c "cat /etc/passwd"
    echo "Pulse enter para continuar"
    sh -c "read enter"
    echo "Mostramos /etc/shadow"
    sh -c "cat /etc/shadow"
fi