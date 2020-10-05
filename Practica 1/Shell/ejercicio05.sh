#!/bin/bash

echo -e "Los grupos del sistema son los siguientes"
awk -F":" '$3 >= 1000 { print $0 }' /etc/group