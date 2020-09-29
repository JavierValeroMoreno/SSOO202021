#!/bin/bash

function menu(){
    echo "1- Configuracion red"
    echo "2- Conexiones red"
    echo "3- Procesos activos"
    echo "4- Consumo de memoria"
    echo "5- Espacio de disco disponible"
    echo "6- Espacio de disco usado"
    echo "0- Salir"
    echo -n "Elija opcion:"
}

function do_menu(){

    case $1 in
    1) ifconfig;;
    2) netstat -atunp;;
    3) top;;
    4) free -m;;
    5) df;;
    6) du;;
    0) ;;
    *) echo "Opcion incorrecta" $1
    esac
}

while [ "$opcion" != "0" ] do

    menu
    read opcion
    do_menu $opcion
done