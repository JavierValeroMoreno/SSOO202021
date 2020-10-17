#!/bin/bash

FICH=/root/contenidoraiz

if [ $? == 0 ]; then
    sh -c "touch $FICH"
    sh -c "ls / >> $FICH"
fi