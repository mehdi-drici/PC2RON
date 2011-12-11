#include "envoi.h"
#include "erreur.h"

/**
 * Envoi d'une trame
 * @todo implementation
 */
int envoyer_trame(SOCKET sock, Trame trameEnvoyee) {    
    int nbOctetsEnvoyes = 0;
    int i = 0;
    
    // Envoi de l'entête
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.fanion), 1, 0);
    //nbOctetsEnvoyes = send(sock, (char*)&(buffer), 1, 0);
    
    if (nbOctetsEnvoyes < 0) {
        return ERR_ENVOI_ENTETE_TRAME;
    }
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.id), 1, 0);
    if (nbOctetsEnvoyes < 0) {    
        return ERR_ENVOI_ENTETE_TRAME;
    }
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.nbDonnees), 1, 0);
    if (nbOctetsEnvoyes < 0) {
        return ERR_ENVOI_ENTETE_TRAME;
    }

    // Envoi des donnees
    for(i=0; i < trameEnvoyee.nbDonnees; i++) {
        envoyer_donnee(sock, trameEnvoyee.donnees[i]);
    }

    return SUCCES;
}

int envoyer_donnee(SOCKET sock, Donnee donneeEnvoyee) {
    int erreur;

    switch(donneeEnvoyee.type)
    {
    case ENTIER_SIGNE1:
        erreur = envoyer_entierSigne1(sock, donneeEnvoyee);
        break;

    case ENTIER_SIGNE2:
        erreur = envoyer_entierSigne2(sock, donneeEnvoyee);
        break;

    case ENTIER_SIGNE4:
        erreur = envoyer_entierSigne4(sock, donneeEnvoyee);
        break;

    case ENTIER_NON_SIGNE1:
        erreur = envoyer_entierNonSigne1(sock, donneeEnvoyee);
        break;

    case ENTIER_NON_SIGNE2:
        erreur = envoyer_entierNonSigne2(sock, donneeEnvoyee);
        break;

    case ENTIER_NON_SIGNE4:
        erreur = envoyer_entierNonSigne4(sock, donneeEnvoyee);
        break;

    case CHAINE:

        erreur = envoyer_chaine(sock, donneeEnvoyee);
        break;

    case FLOTTANT:
        erreur = envoyer_flottant(sock, donneeEnvoyee);
        break;

    default:
        erreur = ERR_ENVOI_DONNEE;
    }

    return erreur;
}

int envoyer_entierSigne1(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    //long donnees = htons(entierEnvoye.entierSigne2);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0) {
        //fprintf(stderr, "%s: Erreur d'envoi d'entete de l'entier signe 1\n", __func__);
        return ERREUR;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, &(entier.entierSigne1), 1, 0);
    if (nbOctetsRecus < 0) {
        fprintf(stderr, "%s: Erreur d'envoi de l'entier signe 1\n", __func__);
        return ERREUR;
    }

    return SUCCES;
}

int envoyer_entierSigne2(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    short donnees = htons(entier.entierSigne2);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_INT16;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, (char*)&donnees, 2, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_INT16;
    }

    return SUCCES;
}

int envoyer_entierSigne4(SOCKET sock, Donnee entierEnvoye) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    long donnees = htonl(entierEnvoye.entierSigne4);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)entierEnvoye.type, 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_INT32;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, (char*)&donnees, 4, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_INT16;
    }

    return SUCCES;
}

int envoyer_entierNonSigne1(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_UINT8;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, &(entier.entierNonSigne1), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_INT16;
    }

    return SUCCES;
}

int envoyer_entierNonSigne2(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    unsigned short donnees = htons(entier.entierSigne2);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_UINT16;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, (char*)&donnees, 2, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_UINT16;
    }

    return SUCCES;
}

int envoyer_entierNonSigne4(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    unsigned long donnees = htonl(entier.entierNonSigne4);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_UINT32;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, (char*)&donnees, 4, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_UINT16;
    }

    return SUCCES;
}

int envoyer_chaine(SOCKET sock, Donnee chaine) {
    int nbOctetsRecus = 0;
    
    // On convertit data en entier big-endian
    unsigned short taille = htons(chaine.chaine.taille);
    
    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(chaine.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_CHAINE;
    }

    // Envoi de la taille de la chaine
    nbOctetsRecus = send(sock, (char*)&taille, 2, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_TAILLE_CHAINE;
    }

    // Envoi de la chaine
    
    nbOctetsRecus = send(sock, chaine.chaine.texte, chaine.chaine.taille, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_CHAINE;
    }

    return SUCCES;
}

// @TODO Conversion Double en Octets
int envoyer_flottant(SOCKET sock, Donnee flottantEnvoye) {
    /*
    int nbOctetsRecus = 0;
    char donnees[8];


    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(flottantEnvoye.type), 1, 0);
    if (nbOctetsRecus < 0) {
    	return ERR_ENVOI_ENTETE_FLOTTANT;
    }

    // Envoi du flottant
    donnees[0] = (flottantEnvoye.flottant >> 56) & 0xFF;
    donnees[1] = (flottantEnvoye.flottant >> 48) & 0xFF;
    donnees[2] = (flottantEnvoye.flottant >> 40) & 0xFF;
    donnees[3] = (flottantEnvoye.flottant >> 32) & 0xFF;
    donnees[4] = (flottantEnvoye.flottant >> 24) & 0xFF;
    donnees[5] = (flottantEnvoye.flottant >> 16) & 0xFF;
    donnees[6] = (flottantEnvoye.flottant >> 8) & 0xFF;
    donnees[7] = (flottantEnvoye.flottant >> 0) & 0xFF;

    nbOctetsRecus = send(sock, donnees, 8, 0);
    if (nbOctetsRecus < 0) {
    	return ERR_ENVOI_FLOTTANT;
    }
    */
    return SUCCES;
}
