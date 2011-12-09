/*
 * trame.c
 *
 *  Created on: 27 nov. 2011
 *      Author: Mehdi Drici
 */

#include "trame.h"

// Premier octet de la trame
//const char FANION = 0xFF;
//const char FIN_TRANSMISSION = 0x00;


// @TODO Problèmes de réallocation
void ajouter_donnee(Trame* t, Donnee d)
{
    int taille = t->nbDonnees;

    /* Premier ajout de donnée */
    if (taille == 0)
    {
        t->donnees = malloc(sizeof(Donnee));

        /* On réalloue à chaque nouvel ajout */
    }
    else
    {
        t->donnees = realloc(t->donnees, (taille+1) * sizeof(Donnee));
    }

    t->donnees[taille] = d;
    (t->nbDonnees)++;
}

// @todo implementation
void ajouter_donnees(Trame* t, Donnee* d) {

}


/**
 * Affichage d'une trame ou d'une donnée
 */
void afficher_trame(Trame trame) {
    int i = 0;

    printf("{ ");
    
    switch(trame.fanion) {
        case TRAME_NORMALE:
            // Affichage de l'ID au format hexadecimal
            printf("%#2.2X", trame.id);

            // Affichage des données
            for (i=0; i < trame.nbDonnees; i++) {
                printf(", ");
                afficher_donnee(trame.donnees[i]);
            }
            break;
            
        case TRAME_SPECIALE:
            printf("END");
            break;
          
        default:
            printf("Erreur de trame\n");
    }
    
    printf(" }\n");
}

void afficher_donnee(Donnee donnee) {
    int i=0;
    
    switch(donnee.type)
    {
    case ENTIER_SIGNE1:
        printf("int8 %d", donnee.entierSigne1);
        break;

    case ENTIER_SIGNE2:
        printf("int16 %d", donnee.entierSigne2);
        break;

    case ENTIER_SIGNE4:
        printf("int32 %d", donnee.entierSigne4);
        break;

    case ENTIER_NON_SIGNE1:
        printf("uint8 %u", donnee.entierNonSigne1);
        break;

    case ENTIER_NON_SIGNE2:
        printf("uint16 %u", donnee.entierNonSigne2);
        break;

    case ENTIER_NON_SIGNE4:
        printf("uint32 %u", donnee.entierNonSigne4);
        break;

    case CHAINE:
        printf("string \"");
        
        for(i=0; i < donnee.chaine.taille; i++) {
            if(donnee.chaine.texte[i] < 32 || donnee.chaine.texte[i] > 127) {
                printf("\\x%X", donnee.chaine.texte[i]);
            } else {
                printf("%c", donnee.chaine.texte[i]);
            }
        }
        printf("\"");
        break;

    case FLOTTANT:
        printf("double %f", donnee.flottant);
        break;

    default:
        printf("Mauvais type !\n");
    }
}