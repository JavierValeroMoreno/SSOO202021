#!bin/bash

FICH=/root/contenidoraiz

if [ $? == 0] then
    touch $FICH
    ls / >> $FICH
fi