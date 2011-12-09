#!/bin/bash

cd PC2RON_Serveur
gcc -c *.c
gcc *.o -o pc2ron_serveur.exe -lpthread

./pc2ron_serveur.exe
