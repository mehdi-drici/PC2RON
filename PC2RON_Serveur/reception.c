#include "reception.h"
#include "erreur.h"
#include <errno.h>
#include <stdlib.h>

/**
 * Réception d'une trame ou d'une donnée
 */

//@TODO implementer
Trame* recevoir_trame(SOCKET sock){
    Trame* trameRecue = malloc(sizeof(Trame));
    unsigned char octet;
    int i = 0;
    int nbOctetsRecus = 0;
    Donnee d;

    trameRecue->nbDonnees = 0;
    
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, nbOctetsRecus, trameRecue);
    trameRecue->fanion = octet;
    
    switch (octet) {
        case TRAME_NORMALE:
            break;

            // Fin de transmission
        case TRAME_SPECIALE:
            // Fermeture de connexion
            shutdown(sock, SHUT_RDWR);
            return SUCCES;

        default:
            PRINT_UNKNOWN_PENNANT(octet);
            free_trame(trameRecue);
            return NULL;
    }

    // Recuperation de l'id
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, nbOctetsRecus, trameRecue);
    trameRecue->id = octet;

    // Recuperation du nombre de donnees
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, nbOctetsRecus, trameRecue);
    trameRecue->nbDonnees = octet;
    
    // Recuperation des donnees tant qu'il n'y a pas d'erreur
    while (i < trameRecue->nbDonnees) {
        if(d = recevoir_donnee(sock) == NULL) {
            free_trame(trameRecue);
            return NULL;
        }
        ajouter_donnee(trameRecue, d);
        i++;
    }
    
    return trameRecue;
}

Donnee* recevoir_donnee(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    unsigned char type;

    // Recuperation du type de donnee
    EXIT_IF_ERROR_SEND(sock, recv(sock, &type, 1, 0), donneeRecue);

    // Ajout du type de donnee
    donneeRecue->type = type;
    
    switch(type) {
        case ENTIER_SIGNE1:
            return recevoir_entierSigne1(sock, donneeRecue);

        case ENTIER_SIGNE2:
            return recevoir_entierSigne2(sock, donneeRecue);

        case ENTIER_SIGNE4:
            return recevoir_entierSigne4(sock, donneeRecue);

        case ENTIER_NON_SIGNE1:
            return recevoir_entierNonSigne1(sock, donneeRecue);

        case ENTIER_NON_SIGNE2:
            return recevoir_entierNonSigne2(sock, donneeRecue);

        case ENTIER_NON_SIGNE4:
            return recevoir_entierNonSigne4(sock, donneeRecue);

        case CHAINE:
            return recevoir_chaine(sock, donneeRecue);

        case FLOTTANT:
            return recevoir_flottant(sock, donneeRecue);

        default:
            PRINT_UNKNOWN_DATA_TYPE(type);
            return NULL;
    }
}

Donnee* recevoir_entierSigne1(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    char entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    donneeRecue->entierSigne1 = entierRecu;

    return donneeRecue;
}

Donnee* recevoir_entierSigne2(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    // On convertit l'entier récupéré en little-endian si l'ordinateur
    // stock les entiers en mémoire en little-endian, sinon s'il les
    // stock en big-endian l'entier est convertit en big-endian
    donneeRecue->entierSigne2 = ntohs(entierRecu);

    return donneeRecue;
}

Donnee* recevoir_entierSigne4(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    int entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    donneeRecue->entierSigne4 = ntohl(entierRecu);

    return donneeRecue;
}

Donnee* recevoir_entierNonSigne1(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    unsigned char entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    donneeRecue->entierNonSigne1 = entierRecu;

    return donneeRecue;
}

Donnee* recevoir_entierNonSigne2(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    unsigned short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    donneeRecue->entierNonSigne2 = ntohs(entierRecu);

    return donneeRecue;
}

Donnee* recevoir_entierNonSigne4(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    unsigned long int entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    donneeRecue->entierNonSigne4 = ntohl(entierRecu);

    return donneeRecue;
}

Donnee* recevoir_chaine(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    unsigned char* chaineRecue;
    unsigned short taille, tailleConvertie;

    int nbOctetsRecus = 0;

    // Reception de la taille de la chaine
    nbOctetsRecus = recv(sock, (char*)&taille, 2, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);
    tailleConvertie = ntohs(taille);
    
    // Reception du contenu de la chaine
    chaineRecue = calloc(tailleConvertie, sizeof(char));
    nbOctetsRecus = recv(sock, chaineRecue, tailleConvertie, 0);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    (donneeRecue->chaine).taille = tailleConvertie;
    (donneeRecue->chaine).texte = chaineRecue;
    strcpy((donneeRecue->chaine).texte, chaineRecue);
    
    return donneeRecue;
}

Donnee* recevoir_flottant(SOCKET sock) {
    Donnee* donneeRecue = malloc(sizeof(Donnee));
    double flottantRecu;
    char buffer[8];
    int nbOctetsRecus = 0;
    int i = 0;
    double temp = 0, resultat = 0;

    // On reçoit une suite de 8 octets, le premier octet reçu est toujours l'octet de poids fort
    nbOctetsRecus = recv(sock, (char*)&flottantRecu, 8, 0);
    EXIT_IF_ERROR_RECV_DATA(sock, nbOctetsRecus, donneeRecue);

    // On rassemble les 8 octets séparé en une seul variable de 8 octets
/*
    for (i=1; i < 8; i++)
    {
        temp = buffer[i] << 8*i;
        resultat += temp;
    }
*/
    
    // On fini par copier le résultat dans la donnee
    //donneeRecue->flottant = resultat;
    donneeRecue->flottant = flottantRecu;
            
    return donneeRecue;
}
