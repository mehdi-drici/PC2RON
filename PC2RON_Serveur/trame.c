#include "trame.h"
#include "erreur.h"
#include <stdio.h>
#include <stdlib.h>

void ajouter_donnee(Trame t, Donnee d) {
    unsigned int taille = t->nbDonnees;

    /* Premier ajout de donnée */
    if (taille == 0) {
        t->donnees = malloc(sizeof(struct Donnee));

        /* On réalloue à chaque nouvel ajout */
    } else {
        t->donnees = realloc(t->donnees, (taille+1) * sizeof(struct Donnee));
    }

    t->donnees[taille] = d;
    (t->nbDonnees)++;
}

   /*   @todo implementation  */ 
void ajouter_donnees(Trame t, Donnee d) {

}


/**
 * Affichage d'une trame ou d'une donnée
 */
void afficher_trame(Trame trame) {
    int i = 0;

    printf(">>> { ");

    switch(trame->fanion) {
        case TRAME_NORMALE:
               /*   Affichage de l'ID au format hexadecimal  */ 
            printf("%#2.2X", trame->id);

               /*   Affichage des données  */ 
            for (i=0; i < trame->nbDonnees; i++) {
                printf(", ");
                afficher_donnee(trame->donnees[i]);
            }
            break;
            
        case TRAME_SPECIALE:
            printf("%s", S_END);
            break;
          
        default:
            PRINT_UNKNOWN_PENNANT(trame->fanion);
    }
    
    printf(" }\n");
}

void afficher_donnee(Donnee donnee) {
    int i = 0;
    
    switch(donnee->type) {
        case ENTIER_SIGNE1:
            printf("%s %d", S_INT8, donnee->entierSigne1);
            break;

        case ENTIER_SIGNE2:
            printf("%s %d", S_INT16, donnee->entierSigne2);
            break;

        case ENTIER_SIGNE4:
            printf("%s %d", S_INT32, donnee->entierSigne4);
            break;

        case ENTIER_NON_SIGNE1:
            printf("%s %u", S_UINT8, donnee->entierNonSigne1);
            break;

        case ENTIER_NON_SIGNE2:
            printf("%s %u", S_UINT16, donnee->entierNonSigne2);
            break;

        case ENTIER_NON_SIGNE4:
            printf("%s %u", S_UINT32, donnee->entierNonSigne4);
            break;

        case CHAINE:
            printf("%s \"", S_STRING);

            for(i=0; i < donnee->chaine.taille; i++) {
                if(donnee->chaine.texte[i] < 32 || donnee->chaine.texte[i] > 127) {
                    printf("\\x%X", donnee->chaine.texte[i]);
                } else {
                    printf("%c", donnee->chaine.texte[i]);
                }
            }
            printf("\"");
            break;

        case FLOTTANT:
            printf("%s %f", S_DOUBLE, donnee->flottant);
            break;

        default:
            PRINT_UNKNOWN_DATA_TYPE(donnee->type);
    }
}

void free_trame(Trame t) {
    int i;
    
    for(i=0; i < t->nbDonnees; i++) {
        free(t->donnees[i]);
    }
    
    free(t);
}