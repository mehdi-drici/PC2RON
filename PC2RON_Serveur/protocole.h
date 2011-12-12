/*
 * protocole.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#define NOM_APPLICATION "PC2RON"
#define NOM_VERSION_PROTOCOLE "PC2RON2011"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

/* Chaines de caracteres correspondant aux types de donnee */
#define S_ACK "ACK"
#define S_CONNECT "CONNECT"
#define S_DEATH "DEATH"
#define S_END_OF_LIST "END OF LIST"
#define S_INITIATE "INITIATE"
#define S_ORDER "ORDER"
#define S_PAUSE "PAUSE"
#define S_REGISTERED "REGISTERED"
#define S_START "START"
#define S_USER "USER"
#define S_TURN "TURN"
#define S_WIN "WIN"

// Ordres
#define ORDRE_DROIT "idle"
#define ORDRE_GAUCHE "left"
#define ORDRE_DROITE "right"
#define ORDRE_ABANDON "abandon"

typedef struct Resultat {
    TypeTrame typeTrame;
    void* contenu;
} Resultat;

void init_protocole(Joueurs j);

// Requetes du client
Resultat* get_resultat_echange(SOCKET sock);
char* get_order(SOCKET sock, Trame t);

// Reponses au client
int repondre_initiate(SOCKET sock, Trame t);
Joueur* repondre_connect(SOCKET sock, Trame t);

// Envoi au client
int envoyer_user(SOCKET sock, Joueur j);
int envoyer_users(SOCKET sock, Joueurs j);
int envoyer_end(SOCKET sock);
int envoyer_pause(SOCKET sock, char* message);
int envoyer_start(SOCKET sock, char* message);
int envoyer_turn(SOCKET sock, Joueur j[]);

int envoyer_win(SOCKET sock, unsigned short id);
int envoyer_death(SOCKET sock, unsigned short id);
int envoyer_deaths(SOCKET sock, unsigned short id1, unsigned short id2);

#endif /* PROTOCOLE_H_ */
