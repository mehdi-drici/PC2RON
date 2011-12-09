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

#define TYPE_TRAME_INCONNU -1

/* Code d'erreurs */
typedef enum ERR_PROTOCOLE {
    ERR_SOCKET,
    ERR_INITIATE,
    ERR_CONNECT,
    ERR_ENVOI_TURN,
    ERR_ENVOI_DEATH,
    ERR_ENVOI_WIN,
    ERR_ENTETE_DONNEE,
    ERR_VALEUR_DONNEE
} ERR_PROTOCOLE;

/*
typedef enum Ordre { DROIT, GAUCHE, DROITE, ABANDON } Ordre;
char* sOrdre[4] = {"idle", "left", "right", "abandon"};
*/
// Ordres
#define DROIT "idle"
#define GAUCHE "left"
#define DROITE "right"
#define ABANDON "abandon"

// Messages d'erreur pour la trame Registered
#define MSG_ERR_TRAME "Le format de la trame n'est pas correct"
#define MSG_ERR_RVB "Le format RVB n'est pas correct"
#define MSG_ERR_NOM "Le nom doit etre une chaine de caracteres"
/*
typedef enum MsgErreurReg { 
    MSG_ERR_TRAME, MSG_ERR_RVB, MSG_ERR_NOM 
} MsgErreurReg;

char* sMsgErreurReg[3] = {"Le format de la trame n'est pas correct", 
                        "Le format RVB n'est pas correct", 
                        "Le nom doit etre une chaine de caracteres"};
*/
typedef struct Resultat {
    TypeTrame typeTrame;
    void* contenu;
} Resultat;

// Initialisation de la connexion (socket)
//ERR_PROTOCOLE init(SOCKET socketServeur);

// Requetes du client
Resultat get_resultat(SOCKET sock);
char* get_order(SOCKET sock, Trame t);

// Reponses au client
ERR_PROTOCOLE repondre_initiate(SOCKET sock, Trame t);
/**
 * 
 * @param t
 * @return informations du nouveau joueur connecté
 */
Joueur* repondre_connect(SOCKET sock, Trame t);

// Envoi aux clients
ERR_PROTOCOLE envoyer_user(SOCKET sock, Joueur j);
ERR_PROTOCOLE envoyer_users(SOCKET sock, Joueur j[]);
ERR_PROTOCOLE envoyer_end(SOCKET sock);
ERR_PROTOCOLE envoyer_pause(SOCKET sock, char* message);
ERR_PROTOCOLE envoyer_start(SOCKET sock, char* message);
ERR_PROTOCOLE envoyer_turn(SOCKET sock, Joueur j[]);

#endif /* PROTOCOLE_H_ */
