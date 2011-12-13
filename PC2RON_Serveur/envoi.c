#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
 #include <netinet/in.h>
#include "envoi.h"
#include "erreur.h"

int envoyer_fin_transmission(SOCKET sock) {
    int nbOctetsEnvoyes = 0;
    int trameSpeciale = TRAME_SPECIALE;
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameSpeciale), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
    return SUCCESS;
}

/**
 * Envoi d'une trame
 * @todo implementation
 */
int envoyer_trame(SOCKET sock, Trame trameEnvoyee) {    
    int nbOctetsEnvoyes = 0;
    int i = 0;
    
       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee->fanion), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee->id), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee->nbDonnees), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
       /*   Envoi des donnees tant qu'il n'y a pas d'erreur  */ 
    while (i < trameEnvoyee->nbDonnees) {
        if(envoyer_donnee(sock, trameEnvoyee->donnees[i]) == ERROR) {
            return ERROR;
        }
        i++;
    }
    
    return SUCCESS;
}

int envoyer_donnee(SOCKET sock, Donnee donneeEnvoyee) {
    switch(donneeEnvoyee->type) {
        case ENTIER_SIGNE1:
            return envoyer_entierSigne1(sock, donneeEnvoyee);

        case ENTIER_SIGNE2:
            return envoyer_entierSigne2(sock, donneeEnvoyee);

        case ENTIER_SIGNE4:
            return envoyer_entierSigne4(sock, donneeEnvoyee);

        case ENTIER_NON_SIGNE1:
            return envoyer_entierNonSigne1(sock, donneeEnvoyee);

        case ENTIER_NON_SIGNE2:
            return envoyer_entierNonSigne2(sock, donneeEnvoyee);

        case ENTIER_NON_SIGNE4:
            return envoyer_entierNonSigne4(sock, donneeEnvoyee);

        case CHAINE:
            return envoyer_chaine(sock, donneeEnvoyee);

        case FLOTTANT:
            return  envoyer_flottant(sock, donneeEnvoyee);

        default:
            return ERROR;
    }
}

int envoyer_entierSigne1(SOCKET sock, Donnee entier) {
    int nbOctetsEnvoyes = 0;

       /*   On convertit data en entier big-endian  */ 
       /*  long donnees = htons(entierEnvoye->entierSigne2);  */ 

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(entier->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, &(entier->entierSigne1), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_entierSigne2(SOCKET sock, Donnee entier) {
    int nbOctetsEnvoyes = 0;

       /*   On convertit data en entier big-endian  */ 
    short donnees = htons(entier->entierSigne2);

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(entier->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, (char*)&donnees, 2, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_entierSigne4(SOCKET sock, Donnee entierEnvoye) {
    int nbOctetsEnvoyes = 0;

    /*   On convertit data en entier big-endian  */ 
    
    long donnees = htonl((uint32_t) entierEnvoye->entierSigne4);

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)entierEnvoye->type, 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, (char*)&donnees, 4, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_entierNonSigne1(SOCKET sock, Donnee entier) {
    int nbOctetsEnvoyes = 0;

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(entier->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, &(entier->entierNonSigne1), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_entierNonSigne2(SOCKET sock, Donnee entier) {
    int nbOctetsEnvoyes = 0;

       /*   On convertit data en entier big-endian  */ 
    unsigned short donnees = htons(entier->entierSigne2);

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(entier->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, (char*)&donnees, 2, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_entierNonSigne4(SOCKET sock, Donnee entier) {
    int nbOctetsEnvoyes = 0;

       /*   On convertit data en entier big-endian  */ 
    unsigned long donnees = htonl(entier->entierNonSigne4);

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(entier->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de l'entier  */ 
    nbOctetsEnvoyes = send(sock, (char*)&donnees, 4, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

    return SUCCESS;
}

int envoyer_chaine(SOCKET sock, Donnee chaine) {
    int nbOctetsEnvoyes = 0;
    
       /*   On convertit data en entier big-endian  */ 
    unsigned short taille = htons(chaine->chaine.taille);
    
       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(chaine->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de la taille de la chaine  */ 
    nbOctetsEnvoyes = send(sock, (char*)&taille, 2, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi de la chaine  */ 
    nbOctetsEnvoyes = send(sock, chaine->chaine.texte, chaine->chaine.taille, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
        
    return SUCCESS;
}

   /*   @TODO Conversion Double en Octets  */ 
int envoyer_flottant(SOCKET sock, Donnee flottantEnvoye) {
    int nbOctetsEnvoyes = 0;
    char donnees[8];

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(flottantEnvoye->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi du flottant  */ 
    /*
    @todo codage du flottant
    donnees[0] = (flottantEnvoye->flottant >> 56) & 0xFF;
    donnees[1] = (flottantEnvoye->flottant >> 48) & 0xFF;
    donnees[2] = (flottantEnvoye->flottant >> 40) & 0xFF;
    donnees[3] = (flottantEnvoye->flottant >> 32) & 0xFF;
    donnees[4] = (flottantEnvoye->flottant >> 24) & 0xFF;
    donnees[5] = (flottantEnvoye->flottant >> 16) & 0xFF;
    donnees[6] = (flottantEnvoye->flottant >> 8) & 0xFF;
    donnees[7] = (flottantEnvoye->flottant >> 0) & 0xFF;
     */
    
    nbOctetsEnvoyes = send(sock, donnees, 8, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
    return SUCCESS;
}
