/*
 * protocole.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#include "trame.h"

/* Code d'erreurs */
typedef enum ERR_PROTOCOLE {
    ERR_INITIATE,
    ERR_CONNECT,
    ERR_ENVOI_TURN,
    ERR_ENVOI_DEATH,
    ERR_ENVOI_WIN,
    ERR_ENTETE_DONNEE,
    ERR_VALEUR_DONNEE
} ERR_PROTOCOLE;

typedef enum TypeTrame {
	Ack = 0x41,
	Connect = 0x43,
	End = 0x45,
	Initiate = 0x49,
	Pause = 0x50,
	Registered = 0x52,
	Start = 0x53,
	User = 0x55
} TYPE_TRAME;

typedef enum Ordre {
    droit = "idle",
    gauche = "left",
    droite = "right",
    abandon = "abandon"
} Ordre;

// Requetes du client
Ordre get_order(Trame t);

// Reponses au client
ERR_PROTOCOLE repondre_initiate(Trame t);
/**
 * 
 * @param t
 * @return informations du nouveau joueur connecté
 */
Joueur repondre_connect(Trame t);

// Envoi aux clients
ERR_PROTOCOLE envoyer_user(Joueur j);
ERR_PROTOCOLE envoyer_users(Joueur j[]);
ERR_PROTOCOLE envoyer_end();
ERR_PROTOCOLE envoyer_pause(char* message);
ERR_PROTOCOLE envoyer_start(char* message);
ERR_PROTOCOLE envoyer_turn(Joueur j[]);

#endif /* PROTOCOLE_H_ */
