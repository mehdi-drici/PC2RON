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
#define NOT_CONNECTED -1

#include "joueur.h"
#include "trame.h"

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

typedef enum TypeTrame {
	Ack = 0x41,
	Connect = 0x43,
        Death = 0x44,
	End = 0x45,
	Initiate = 0x49,
        Order = 0x4F,
	Pause = 0x50,
	Registered = 0x52,
	Start = 0x53,
	User = 0x55,
        Turn = 0x54,
        Win = 0x57
} TypeTrame;

typedef struct Resultat {
    int typeTrame;
    void* contenu;
} Resultat;

/*void init_protocole(Joueurs j);*/

   /*   Requetes du client  */ 
Resultat* get_resultat_echange(int sock, Joueurs lesJoueurs);
char* get_order(int sock, Trame t, Joueurs lesJoueurs);

   /*   Reponses au client  */ 
int repondre_initiate(int sock, Trame t, Joueurs lesJoueurs);
Joueur repondre_connect(int sock, Trame t, Joueurs lesJoueurs);

   /*   Envoi au client  */ 

/* @todo modifier*/
int envoyer_user(int sock, Joueur j);
int envoyer_users(int sock, Joueurs lesJoueurs);

int envoyer_end(int sock, Joueurs lesJoueurs);
int envoyer_pause(int sock, const char* message, Joueurs lesJoueurs);
int envoyer_start(int sock, const char* message, Joueurs lesJoueurs);
int envoyer_turn(int sock, Joueurs lesJoueurs);

int envoyer_win(int sock, unsigned short id, Joueurs lesJoueurs);
int envoyer_death(int sock, unsigned short id, Joueurs lesJoueurs);
int envoyer_deaths(int sock, unsigned short id1, unsigned short id2, 
                                                    Joueurs lesJoueurs);
void deconnecter_joueur(Joueur j);

#endif /* PROTOCOLE_H_ */
