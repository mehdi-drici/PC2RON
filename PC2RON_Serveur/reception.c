#include "reception.h"

/**
 * Réception d'une trame ou d'une donnée
 */

//@TODO implementer
ERREUR_TRAME recevoir_trame(SOCKET sock, Trame* trameRecue){
    unsigned char octet;
    int taille = 0;
    int i = 0;
    int nbOctetsRecus = 0;
    Donnee d;

    trameRecue->nbDonnees = 0;
    
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    
    // Probleme de reception
    if (nbOctetsRecus < 0) {
        close (sock);
        fprintf(stderr, "Erreur de reception du fanion\n");
        return ERR_RCPT_FANION_TRAME;
    }
    
    // Le client s'est deconnecte
    if (nbOctetsRecus == 0) {
        close (sock);
        fprintf(stderr, "Le client s'est deconnecte %d\n", sock);
        return ERR_RCPT_TRAME;
    }
    
    trameRecue->fanion = octet;
    
    switch (octet)
    {
    case TRAME_NORMALE:
        break;

        // Fin de transmission
    case TRAME_SPECIALE:
        // Fermeture de connexion
        shutdown(sock, SHUT_RDWR);
        return SUCCES;

    default:
        fprintf(stderr, "Erreur d'entete\n");
        return ERR_ENTETE_TRAME;
    }

    // Recuperation de l'id
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    
    if (nbOctetsRecus < 0)
    {
        //exit(errno);
        fprintf(stderr, "Erreur de recuperation de l'id\n");
        return ERR_RCPT_FANION_TRAME;
    }
    trameRecue->id = octet;

    // Recuperation du nombre de donnees
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    
    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation du nombre de donnees\n");
        return ERR_RCPT_NB_DONNEES_TRAME;
    }

    taille = octet;
    
    // Recuperation des donnees
    for (i=0; i < taille; i++)
    {
        recevoir_donnee(sock, &d);
        ajouter_donnee(trameRecue, d);
    }

    return SUCCES;
}

ERREUR_DONNEE recevoir_donnee(SOCKET sock, Donnee* donneeRecue) {
    ERREUR_DONNEE erreur;
    unsigned char type;

    // Recuperation du type de donnee
    if (recv(sock, &type, 1, 0) < 0)
    {   
        fprintf(stderr, "Erreur de recuperation du type de donnee\n");
        return ERR_RCPT_TYPE_DONNEE;
    }

    // Ajout du type de donnee
    donneeRecue->type = type;
    
    switch(type)
    {
    case ENTIER_SIGNE1:
        erreur = recevoir_entierSigne1(sock, donneeRecue);
        break;

    case ENTIER_SIGNE2:
        erreur = recevoir_entierSigne2(sock, donneeRecue);
        break;

    case ENTIER_SIGNE4:
        erreur = recevoir_entierSigne4(sock, donneeRecue);
        break;

    case ENTIER_NON_SIGNE1:
        erreur = recevoir_entierNonSigne1(sock, donneeRecue);
        break;

    case ENTIER_NON_SIGNE2:
        erreur = recevoir_entierNonSigne2(sock, donneeRecue);
        break;

    case ENTIER_NON_SIGNE4:
        erreur = recevoir_entierNonSigne4(sock, donneeRecue);
        break;

    case CHAINE:
        erreur = recevoir_chaine(sock, donneeRecue);
        break;

    case FLOTTANT:
        erreur = recevoir_flottant(sock, donneeRecue);
        break;

    default:
        erreur = ERR_RCPT_DONNEE;
    }

    return erreur;
}

ERREUR_DONNEE recevoir_entierSigne1(SOCKET sock, Donnee* donneeRecue) {
    char entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier signe 1\n");
        return ERR_RCPT_INT8;
    }

    donneeRecue->entierSigne1 = entierRecu;

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierSigne2(SOCKET sock, Donnee* donneeRecue) {
    short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier signe 2\n");
        return ERR_RCPT_INT16;
    }

    // On convertit l'entier récupéré en little-endian si l'ordinateur
    // stock les entiers en mémoire en little-endian, sinon s'il les
    // stock en big-endian l'entier est convertit en big-endian
    donneeRecue->entierSigne2 = ntohs(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierSigne4(SOCKET sock, Donnee* donneeRecue) {
    int entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier signe 4\n");
        return ERR_RCPT_INT32;
    }

    donneeRecue->entierSigne4 = ntohl(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne1(SOCKET sock, Donnee* donneeRecue) {
    unsigned char entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier non signe 1\n");
        return ERR_RCPT_UINT8;
    }

    donneeRecue->entierNonSigne1 = entierRecu;

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne2(SOCKET sock, Donnee* donneeRecue) {
    unsigned short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier non signe 2\n");
        return ERR_RCPT_UINT16;
    }

    donneeRecue->entierNonSigne2 = ntohs(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne4(SOCKET sock, Donnee* donneeRecue) {
    unsigned long int entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, MSG_WAITALL);

    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de l'entier non signe 4\n");
        return ERR_RCPT_UINT32;
    }

    donneeRecue->entierNonSigne4 = ntohl(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_chaine(SOCKET sock, Donnee* donneeRecue) {
    unsigned char* chaineRecue;
    unsigned short taille, tailleConvertie;

    int nbOctetsRecus = 0;

    // Reception de la taille de la chaine
    nbOctetsRecus = recv(sock, (char*)&taille, 2, MSG_WAITALL);
    if(nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation de la taille de la chaine\n");
        return ERR_RCPT_TAILLE_CHAINE;
    }
    tailleConvertie = ntohs(taille);
    
    // Reception du contenu de la chaine
    chaineRecue = calloc(tailleConvertie, sizeof(char));
    nbOctetsRecus = recv(sock, chaineRecue, tailleConvertie, 0);
    
    if (nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation du contenu de la chaine\n");
        return ERR_RCPT_CHAINE;
    }

    (donneeRecue->chaine).taille = tailleConvertie;
    (donneeRecue->chaine).texte = chaineRecue;
    strcpy((donneeRecue->chaine).texte, chaineRecue);
    return SUCCES;
}

ERREUR_DONNEE recevoir_flottant(SOCKET sock, Donnee* donneeRecue) {
    double flottantRecu;
    char buffer[8];
    int nbOctetsRecus = 0;
    int i = 0;
    double temp = 0, resultat = 0;

    // On reçoit une suite de 8 octets, le premier octet reçu est toujours l'octet de poids fort
    nbOctetsRecus = recv(sock, (char*)&flottantRecu, 8, 0);
    if(nbOctetsRecus < 0)
    {
        fprintf(stderr, "Erreur de recuperation du flottant\n");
        return ERR_RCPT_FLOTTANT;
    }

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
            
    return SUCCES;
}
