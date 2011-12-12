/*
 * protocole.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#include "builder.h"

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

   /*   Ordres  */ 
#define ORDRE_DROIT "idle"
#define ORDRE_GAUCHE "left"
#define ORDRE_DROITE "right"
#define ORDRE_ABANDON "abandon"

typedef struct Resultat {
    TypeTrame typeTrame;
    void* contenu;
} Resultat;

void init_protocole(Joueurs j);

   /*   Requetes du client  */ 
Resultat* get_resultat_echange(SOCKET sock, Joueurs lesJoueurs);
char* get_order(SOCKET sock, Trame t, Joueurs lesJoueurs);

   /*   Reponses au client  */ 
int repondre_initiate(SOCKET sock, Trame t, Joueurs lesJoueurs);
Joueur repondre_connect(SOCKET sock, Trame t, Joueurs lesJoueurs);

   /*   Envoi au client  */ 

/* @todo modifier*/
int envoyer_user(SOCKET sock, Joueur j);
int envoyer_users(SOCKET sock, Joueurs lesJoueurs);

int envoyer_end(SOCKET sock, Joueurs lesJoueurs);
int envoyer_pause(SOCKET sock, const char* message, Joueurs lesJoueurs);
int envoyer_start(SOCKET sock, const char* message, Joueurs lesJoueurs);
int envoyer_turn(SOCKET sock, Joueurs lesJoueurs);

int envoyer_win(SOCKET sock, unsigned short id, Joueurs lesJoueurs);
int envoyer_death(SOCKET sock, unsigned short id, Joueurs lesJoueurs);
int envoyer_deaths(SOCKET sock, unsigned short id1, unsigned short id2, 
                                                    Joueurs lesJoueurs);

#endif /* PROTOCOLE_H_ */
