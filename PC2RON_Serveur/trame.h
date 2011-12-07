/*
 * trame.h
 *
 *  Created on: 27 nov. 2011
 *      Author: Mehdi Drici
 */

#ifndef TRAME_H_
#define TRAME_H_

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

typedef int SOCKET;

/* Premier octet d'une trame */
//#define FANION 0xFF;
//#define FIN_TRANSMISSION 0x00;

/* Code d'erreurs pour la lecture d'une trame */
typedef enum ERREUR_TRAME {
	ERR_ENTETE_TRAME,
	ERR_ENVOI_ENTETE_TRAME,
	ERR_RCPT_FANION_TRAME,
	ERR_RCPT_NB_DONNEES_TRAME,
        ERR_RCPT_TRAME
} ERREUR_TRAME;

/* Code d'erreurs pour la lecture ou conversion d'une donnée */
typedef enum ERREUR_DONNEE {
	SUCCES,
	ERR_ENVOI_DONNEE,
	ERR_ENVOI_INT8,
	ERR_ENVOI_INT16,
	ERR_ENVOI_INT32,
	ERR_ENVOI_UINT8,
	ERR_ENVOI_UINT16,
	ERR_ENVOI_UINT32,
	ERR_ENVOI_CHAINE,
	ERR_ENVOI_FLOTTANT,

	ERR_ENVOI_ENTETE_INT8,
	ERR_ENVOI_ENTETE_INT16,
	ERR_ENVOI_ENTETE_INT32,
	ERR_ENVOI_ENTETE_UINT8,
	ERR_ENVOI_ENTETE_UINT16,
	ERR_ENVOI_ENTETE_UINT32,
	ERR_ENVOI_ENTETE_CHAINE,
	ERR_ENVOI_TAILLE_CHAINE,
	ERR_ENVOI_ENTETE_FLOTTANT,
	ERR_ENVOI_ENTETE_TAILLE_CHAINE,
	ERR_ENVOI_ENTETE_ENTETE_CHAINE,

	ERR_RCPT_DONNEE,
	ERR_RCPT_TYPE_DONNEE,
	ERR_RCPT_INT8,
	ERR_RCPT_INT16,
	ERR_RCPT_INT32,
	ERR_RCPT_UINT8,
	ERR_RCPT_UINT16,
	ERR_RCPT_UINT32,
	ERR_RCPT_CHAINE,
	ERR_RCPT_TAILLE_CHAINE,
	ERR_RCPT_FLOTTANT
} ERREUR_DONNEE;

/* Types de données */
typedef enum TYPE_DONNEE {
	ENTIER_SIGNE1 = 0x01,
	ENTIER_SIGNE2 = 0X02,
	ENTIER_SIGNE4 = 0x04,
	ENTIER_NON_SIGNE1 = 0X11,
	ENTIER_NON_SIGNE2 = 0x12,
	ENTIER_NON_SIGNE4 = 0X14,
	CHAINE = 0x20,
	FLOTTANT = 0x30
} TYPE_DONNEE;

/* Types de fanion */
typedef enum TYPE_FANION {
    TRAME_NORMALE = 0xFF,
    TRAME_SPECIALE = 0x00
} TYPE_FANION;

/* Structure d'une donnée */
typedef struct Donnee {
	TYPE_DONNEE type;
        
	union {
		/* entier signés */
		char entierSigne1;

		/*
		struct entierSigne2 {
			short n;
			unsigned char octets[2];
		} entierSigne2;
		*/
		short entierSigne2;

		/*
		struct entierSigne4 {
			long n;
			unsigned char octets[4];
		} entierSigne4;
		*/
		int entierSigne4;

		/* entiers non signés */
		unsigned char entierNonSigne1;
		/*
		struct entierNonSigne2 {
			unsigned short n;
			unsigned char octets[2];
		} entierNonSigne2;
		*/
		unsigned short entierNonSigne2;

		/*
		struct entierNonSigne4 {
			unsigned long n;
			unsigned char octets[4];
		} entierNonSigne4;
		*/
		unsigned int entierNonSigne4;

		/* chaîne de caractères */
		struct chaine {
			short taille;
                        
                        // on specifie bien que c'est un tableau
                        // de caracteres pour pouvoir connaitre
                        // sa taille par la suite
			unsigned char* texte; 
		} chaine;

		/* flottant */
		/*
		struct flottant {
			double f;
			unsigned char octets[8];
		} flottant;
		*/
		double flottant;
	};
} Donnee;


/* Structure d'une trame */
typedef struct Trame {
        TYPE_FANION fanion;
	unsigned char id;
	unsigned char nbDonnees;
	Donnee* donnees;
} Trame;


/* Fonctions de la couche transport */

/* Création d'une trame ou d'une donnée */
Trame creer_trame(char id);
void ajouter_donnee(Trame* t, Donnee d);
void ajouter_donnees(Trame* t, Donnee d[]);
Donnee creer_entierSigne1(char entier);
Donnee creer_entierSigne2(short entier);
Donnee creer_entierSigne4(long entier);
Donnee creer_entierNonSigne1(unsigned char entier);
Donnee creer_entierNonSigne2(unsigned short entier);
Donnee creer_entierNonSigne4(unsigned long entier);
Donnee creer_chaine(char texte[]);
Donnee creer_flottant(double flottant);

/* Réception d'une trame ou d'une donnée */
ERREUR_TRAME recevoir_trame(SOCKET sock, Trame* trameRecue);
ERREUR_DONNEE recevoir_donnee(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne1(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne2(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne4(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne1(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne2(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne4(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_chaine(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_flottant(SOCKET sock, Donnee* donneeRecue);

/* Envoi d'une trame */
ERREUR_TRAME envoyer_trame(SOCKET sock, Trame trameEnvoyee);
//char** convertir_trame_toBytes(Trame trame);
ERREUR_DONNEE envoyer_donnee(SOCKET sock, Donnee donnee);
ERREUR_DONNEE envoyer_entierSigne1(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierSigne2(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierSigne4(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne1(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne2(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne4(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_chaine(SOCKET sock, Donnee chaine);
ERREUR_DONNEE envoyer_flottant(SOCKET sock, Donnee flottant);

int taille_trame(Trame trame);

/* Affichage d'une trame ou d'une donnee */
void afficher_trame(Trame trame);
void afficher_donnee(Donnee trame);
/*
char* entierSigne1_toString(Donnee entier);
char* entierSigne2_toString(Donnee entier);
char* entierSigne4_toString(Donnee entier);
char* entierNonSigne1_toString(Donnee entier);
char* entierNonSigne2_toString(Donnee entier);
char* entierNonSigne4_toString(Donnee entier);
char* chaine_toString(Donnee chaine);
char* flottant_toString(Donnee flottant);
*/

#endif /* TRAME_H_ */
