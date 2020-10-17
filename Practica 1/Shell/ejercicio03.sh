#!/bin/bash


if [ $? == 0 ]; then
    sh -c "touch /root/contenidoraiz"
    sh -c "ls / > /root/contenidoraiz"
fi