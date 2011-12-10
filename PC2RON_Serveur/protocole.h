/*
 * protocole.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#include "builder.h"
#include "protocole.h"

#define NOM_APPLICATION "PC2RON"
#define NOM_VERSION_PROTOCOLE "PC2RON2011"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define TYPE_TRAME_INCONNU -1

/* Code d'erreurs */
typedef enum ERR_PROTOCOLE {
    ERR_SOCKET = 1,
    ERR_INITIATE = 2,
    ERR_CONNECT = 3,
    ERR_TURN = 4,
    ERR_DEATH = 5,
    ERR_WIN = 6,
    ERR_ORDER = 7,
    ERR_ENTETE_DONNEE = 8,
    ERR_VALEUR_DONNEE = 9,
    ERR_TYPE_INCONNU = 10
} ERR_PROTOCOLE;

// Ordres
#define ORDRE_DROIT "idle"
#define ORDRE_GAUCHE "left"
#define ORDRE_DROITE "right"
#define ORDRE_ABANDON "abandon"

// Messages d'erreur pour la trame Registered (Client)
#define MSG_ERR_TRAME "Le format de la trame n'est pas correct"
#define MSG_ERR_RVB "Le format RVB n'est pas correct"
#define MSG_ERR_NOM "Le nom doit etre une chaine de caracteres"

// Messages d'erreur pour le serveur
#define MSG_ERR_CONNECT(sock) "Problème d'inscription de la socket %d", sock
#define MSG_ERR_ORDER(sock) "L'ordre reçu par la socket %d n'est pas correct", sock
#define MSG_ERR_TYPE_INCONNU "Le type de la trame reçue est inconnu"

typedef struct Resultat {
    TypeTrame typeTrame;
    ERR_PROTOCOLE erreur;
    char* msgErr;
    void* contenu;
} Resultat;

// Requetes du client
Resultat get_resultat_echange(SOCKET sock);
char* get_order(SOCKET sock, Trame t);

// Reponses au client
ERR_PROTOCOLE repondre_initiate(SOCKET sock, Trame t);
Joueur* repondre_connect(SOCKET sock, Trame t);

// Envoi au client
ERR_PROTOCOLE envoyer_user(SOCKET sock, Joueur j);
ERR_PROTOCOLE envoyer_users(SOCKET sock, Joueur j[]);
ERR_PROTOCOLE envoyer_end(SOCKET sock);
ERR_PROTOCOLE envoyer_pause(SOCKET sock, char* message);
ERR_PROTOCOLE envoyer_start(SOCKET sock, char* message);
ERR_PROTOCOLE envoyer_turn(SOCKET sock, Joueur j[]);

ERR_PROTOCOLE envoyer_win(SOCKET sock, unsigned short id);
ERR_PROTOCOLE envoyer_death(SOCKET sock, unsigned short id);
ERR_PROTOCOLE envoyer_deaths(SOCKET sock, unsigned short id1, unsigned short id2);

#endif /* PROTOCOLE_H_ */
