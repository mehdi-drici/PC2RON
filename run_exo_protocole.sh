#!/bin/bash

cd PC2RON_Serveur
gcc -c PC2RON_Serveur/*.c
gcc PC2RON/*.o -o pc2ron_serveur.exe -lpthread

./PC2RON_Serveur/pc2ron_serveur.exe
