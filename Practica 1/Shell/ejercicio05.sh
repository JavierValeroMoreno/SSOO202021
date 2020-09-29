#!/bin/bash

echo -e "Los grupos del sistema son los siguientes"
cut -d':' -f1 /etc/group 