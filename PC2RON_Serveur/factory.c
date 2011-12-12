#include <stdlib.h>
#include <string.h>
#include "factory.h"

/**
 * Création d'une trame ou d'une donnée
 */
Trame creer_trame(unsigned char id) {
    Trame t = malloc(sizeof(struct Trame));
    
    t->fanion = TRAME_NORMALE;
    t->id = id;
    t->nbDonnees = 0;
    t->donnees = malloc(sizeof(struct Donnee));

    return t;
}

Donnee creer_entierSigne1(char entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_SIGNE1;
    d->entierSigne1 = entier;

    return d;
}

Donnee creer_entierSigne2(short entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_SIGNE2;
    d->entierSigne2 = entier;

    return d;
}

Donnee creer_entierSigne4(long entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_SIGNE4;
    d->entierSigne4 = entier;

    return d;
}

Donnee creer_entierNonSigne1(unsigned char entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_NON_SIGNE1;
    d->entierNonSigne1 = entier;

    return d;
}

Donnee creer_entierNonSigne2(unsigned short entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_NON_SIGNE2;
    d->entierNonSigne2 = entier;

    return d;
}

Donnee creer_entierNonSigne4(unsigned long entier) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = ENTIER_NON_SIGNE4;
    d->entierNonSigne4 = entier;

    return d;
}

Donnee creer_chaine(const char* texte) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = CHAINE;
    d->chaine.taille = (unsigned short) strlen(texte);
    /*d->chaine.texte = texte;*/
    

       /*   allocation mémoire pour le stockage   */ 
       /*   de taille+1 cacractères (caractère '\0')  */ 
       /*  memmove(d->chaine.texte[0], texte, strlen(texte) + 1);  */ 

    d->chaine.texte = calloc(strlen(texte), sizeof(char));
    
    strcpy(d->chaine.texte, texte);
    return d;
}

Donnee creer_flottant(double flottant) {
    Donnee d = malloc(sizeof(struct Donnee));
    d->type = FLOTTANT;
    d->flottant = flottant;

    return d;
}
