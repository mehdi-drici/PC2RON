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

/**
 * Création d'une trame ou d'une donnée
 */
Trame creer_trame(char id)
{
    Trame t;
    t.fanion = TRAME_NORMALE;
    t.id = id;
    t.nbDonnees = 0;
    t.donnees = NULL;

    return t;
}

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
void ajouter_donnees(Trame* t, Donnee* d)
{

}

Donnee creer_entierSigne1(char entier)
{
    Donnee d;
    d.type = ENTIER_SIGNE1;
    d.entierSigne1 = entier;

    return d;
}

Donnee creer_entierSigne2(short entier)
{
    Donnee d;
    d.type = ENTIER_SIGNE2;
    d.entierSigne2 = entier;

    return d;
}

Donnee creer_entierSigne4(long entier)
{
    Donnee d;
    d.type = ENTIER_SIGNE4;
    d.entierSigne4 = entier;

    return d;
}

Donnee creer_entierNonSigne1(unsigned char entier)
{
    Donnee d;
    d.type = ENTIER_NON_SIGNE1;
    d.entierNonSigne1 = entier;

    return d;
}

Donnee creer_entierNonSigne2(unsigned short entier)
{
    Donnee d;
    d.type = ENTIER_NON_SIGNE2;
    d.entierNonSigne2 = entier;

    return d;
}

Donnee creer_entierNonSigne4(unsigned long entier)
{
    Donnee d;
    d.type = ENTIER_NON_SIGNE4;
    d.entierNonSigne4 = entier;

    return d;
}

Donnee creer_chaine(char texte[]){
    Donnee d;
    d.type = CHAINE;
    d.chaine.taille = strlen(texte);
    //d.chaine.texte = texte;
    
    // allocation mémoire pour le stockage 
    // de taille+1 cacractères (caractère '\0')
    //memmove(&d.chaine.texte[0], texte, strlen(texte) + 1);
    d.chaine.texte = calloc(strlen(texte) + 1, sizeof(char));
    
    strcpy(d.chaine.texte, texte);
    return d;
}

Donnee creer_flottant(double flottant){
    Donnee d;
    d.type = FLOTTANT;
    d.flottant = flottant;

    return d;
}

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

    // Recuperation du fanion
    //debug
    //printf("Reception...\n");
    //debug
    
    nbOctetsRecus = recv(sock, &octet, 1, 0);
    
    //printf("nbOctetsRecus = %d\n", nbOctetsRecus);
    
    if (nbOctetsRecus < 0) {
        //debug
        //printf("Erreur reception fanion !\n");
        //debug
        //debug
        //printf("Socket fermee !\n");
        //debug
        //fprintf (stderr, "Socket %d fermee\n", sock);
        close (sock);
        return ERR_RCPT_FANION_TRAME;
    }
    
    if (nbOctetsRecus == 0) {
        //debug
        //printf("Socket fermee !\n");
        //debug
        //fprintf (stderr, "Socket %d fermee\n", sock);
        close (sock);
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
        //close(sock);
        return SUCCES;

    default:
        printf("Erreur d'entete\n");
        return ERR_ENTETE_TRAME;
    }

    // Recuperation de l'id
    nbOctetsRecus = recv(sock, &octet, 1, 0);

    if (nbOctetsRecus < 0)
    {
        exit(errno);
        return ERR_RCPT_FANION_TRAME;
    }
    trameRecue->id = octet;

    // Recuperation du nombre de donnees
    nbOctetsRecus = recv(sock, &octet, 1, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_NB_DONNEES_TRAME;
    }

    taille = octet;
    
    //debug
    //printf("Taille = %d\n", taille);
    //debug
    
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
    char type;

    // Recuperation du type de donnee
    if (recv(sock, &type, 1, 0) < 0)
    {
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
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_INT8;
    }

    donneeRecue->entierSigne1 = entierRecu;

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierSigne2(SOCKET sock, Donnee* donneeRecue) {
    short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, 0);

    if (nbOctetsRecus < 0)
    {
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
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_INT32;
    }

    donneeRecue->entierSigne4 = ntohl(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne1(SOCKET sock, Donnee* donneeRecue) {
    unsigned char entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 1, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_UINT8;
    }

    donneeRecue->entierNonSigne1 = entierRecu;

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne2(SOCKET sock, Donnee* donneeRecue) {
    unsigned short entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 2, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_UINT16;
    }

    donneeRecue->entierNonSigne2 = ntohs(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_entierNonSigne4(SOCKET sock, Donnee* donneeRecue) {
    unsigned long int entierRecu;
    int nbOctetsRecus = 0;

    // On récupère l'entier en big-endian
    nbOctetsRecus = recv(sock, (char*)&entierRecu, 4, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_UINT32;
    }

    donneeRecue->entierNonSigne4 = ntohl(entierRecu);

    return SUCCES;
}

ERREUR_DONNEE recevoir_chaine(SOCKET sock, Donnee* donneeRecue) {
    unsigned char* chaineRecue;
    short taille, tailleConvertie;

    int nbOctetsRecus = 0;

    // Reception de la taille de la chaine
    nbOctetsRecus = recv(sock, (char*)&taille, 2, 0);
    if(nbOctetsRecus < 0)
    {
        return ERR_RCPT_TAILLE_CHAINE;
    }
    tailleConvertie = ntohs(taille);

    // Reception du contenu de la chaine
    chaineRecue = calloc(tailleConvertie, sizeof(char));
    nbOctetsRecus = recv(sock, chaineRecue, tailleConvertie, 0);

    if (nbOctetsRecus < 0)
    {
        return ERR_RCPT_CHAINE;
    }

    (donneeRecue->chaine).taille = tailleConvertie;
    //(donneeRecue->chaine).texte = chaineRecue;
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

/**
 * Envoi d'une trame
 * @todo implementation
 */
ERREUR_TRAME envoyer_trame(SOCKET sock, Trame trameEnvoyee) {
    char buffer = 1;
    
    int nbOctetsEnvoyes = 0;
    int i = 0;

    //debug
/*
    printf("trameEnvoyee.fanion = %d\n", trameEnvoyee.fanion);
    printf("@trameEnvoyee.fanion = %p\n", &(trameEnvoyee.fanion));
    printf("trameEnvoyee.id = %d\n", trameEnvoyee.id);
    printf("trameEnvoyee.nbDonnees = %d\n", trameEnvoyee.nbDonnees);
*/
    //debug
    
    // Envoi de l'entête
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.fanion), 1, 0);
    //nbOctetsEnvoyes = send(sock, (char*)&(buffer), 1, 0);
    
    if (nbOctetsEnvoyes < 0)
    {
        //debug
        printf("ERREUR d'envoi du fanion !!!!\n");
        //debug
        
        return ERR_ENVOI_ENTETE_TRAME;
    }
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.id), 1, 0);
    if (nbOctetsEnvoyes < 0)
    {
        //debug
        printf("ERREUR d'envoi de l'ID !!!!\n");
        //debug
        
        return ERR_ENVOI_ENTETE_TRAME;
    }
    
    nbOctetsEnvoyes = send(sock, (char*)&(trameEnvoyee.nbDonnees), 1, 0);
    if (nbOctetsEnvoyes < 0)
    {
        //debug
        printf("ERREUR d'envoi du nombre de donnees !!!!\n");
        //debug
        
        return ERR_ENVOI_ENTETE_TRAME;
    }

    // Envoi des donnees
    for(i=0; i < trameEnvoyee.nbDonnees; i++) {
        envoyer_donnee(sock, trameEnvoyee.donnees[i]);
    }

    return SUCCES;
}

ERREUR_DONNEE envoyer_donnee(SOCKET sock, Donnee donneeEnvoyee) {
    ERREUR_DONNEE erreur;

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

ERREUR_DONNEE envoyer_entierSigne1(SOCKET sock, Donnee entier) {
    int nbOctetsRecus = 0;

    // On convertit data en entier big-endian
    //long donnees = htons(entierEnvoye.entierSigne2);

    // Envoi de l'entête
    nbOctetsRecus = send(sock, (char*)&(entier.type), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_ENTETE_INT8;
    }

    // Envoi de l'entier
    nbOctetsRecus = send(sock, &(entier.entierSigne1), 1, 0);
    if (nbOctetsRecus < 0)
    {
        return ERR_ENVOI_INT16;
    }

    return SUCCES;
}

ERREUR_DONNEE envoyer_entierSigne2(SOCKET sock, Donnee entier) {
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

ERREUR_DONNEE envoyer_entierSigne4(SOCKET sock, Donnee entierEnvoye) {
    int nbOctetsRecus = 0;

    /*
    char donnees[4];

    dataSend[0] = (data >> 24) & 0xFF;
    dataSend[1] = (data >> 16) & 0xFF;
    dataSend[2] = (data >> 8) & 0xFF;
    dataSend[3] = (data >> 0) & 0xFF;

    send(sock, donnees, 4, 0);
    */

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

ERREUR_DONNEE envoyer_entierNonSigne1(SOCKET sock, Donnee entier) {
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

ERREUR_DONNEE envoyer_entierNonSigne2(SOCKET sock, Donnee entier) {
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

ERREUR_DONNEE envoyer_entierNonSigne4(SOCKET sock, Donnee entier) {
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

ERREUR_DONNEE envoyer_chaine(SOCKET sock, Donnee chaine) {
    int nbOctetsRecus = 0;
    
    // On convertit data en entier big-endian
    //unsigned short taille = htons(chaine.chaine.taille);
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
ERREUR_DONNEE envoyer_flottant(SOCKET sock, Donnee flottantEnvoye) {
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


/**
 * Conversion d'une trame ou d'une donnée en chaîne de caractères
 */

void afficher_trame(Trame trame) {
    int i = 0;

    printf(">>> { ");
    
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
    //printf("TYPE = %#0.2x\n", donnee.type);
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
        printf("uint8 %d", donnee.entierNonSigne1);
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
                printf("\\x%d", donnee.chaine.texte[i]);
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

/*
int main(void) {
	printf("Hello world !\n");

	Trame t = creer_trame(73);
	Donnee d = creer_entierSigne1(15);
	Donnee d1 = creer_entierSigne2(-15064);
	Donnee d2 = creer_entierSigne4(12064);
	Donnee d3 = creer_entierNonSigne1(19);
	Donnee d4 = creer_entierNonSigne2(29787);
	Donnee d5 = creer_entierNonSigne4(5698774);
	Donnee d6 = creer_chaine("ceci est un texte");
	Donnee d7 = creer_flottant(15.78987);

	ajouter_donnee(&t, d);
	ajouter_donnee(&t, d1);
	ajouter_donnee(&t, d2);
	ajouter_donnee(&t, d3);
	ajouter_donnee(&t, d4);
	ajouter_donnee(&t, d5);
	ajouter_donnee(&t, d6);
	ajouter_donnee(&t, d7);
	//afficher_donnee(d2);
	afficher_trame(t);

	printf("\n");
	return 0;
}
*/
