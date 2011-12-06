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
typedef enum ERREUR_PROTOCOLE {
	ERREUR_ENTETE_DONNEE = 2,
	ERREUR_VALEUR_DONNEE = 3
} ERREUR_PROTOCOLE;

typedef enum TYPE_TRAME {
	Ack = 0x41,
	Connect = 0x43,
	End = 0x45,
	Initiate = 0x49,
	Pause = 0x50,
	Registered = 0x52,
	Start = 0x53,
	User = 0x55
} TYPE_TRAME;

ERREUR_PROTOCOLE repondre(SOCKET sock, Trame trameRecue);
ERREUR_PROTOCOLE repondreInitiate(SOCKET sock, Trame trameRecue);
ERREUR_PROTOCOLE repondreConnect(SOCKET sock, Trame trameRecue);

void envoyerUser(SOCKET sock);
void envoyerEnd(SOCKET sock);
void envoyerPause(SOCKET sock);
void envoyerStart(SOCKET sock);

#endif /* PROTOCOLE_H_ */
