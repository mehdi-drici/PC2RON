/*
 * trame.h
 *
 *  Created on: 27 nov. 2011
 *      Author: Mehdi Drici
 */

#ifndef TRAME_H_
#define TRAME_H_

typedef int SOCKET;

/* Code d'erreurs pour la lecture d'une trame */
typedef enum ERREUR_TRAME {
        SUCCES,
	ERR_ENTETE_TRAME,
	ERR_ENVOI_ENTETE_TRAME,
	ERR_RCPT_FANION_TRAME,
	ERR_RCPT_NB_DONNEES_TRAME,
        ERR_RCPT_TRAME
} ERREUR_TRAME;

/* Code d'erreurs pour la lecture ou conversion d'une donnée */
typedef enum ERREUR_DONNEE {
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

/* Chaines de caracteres correspondant aux types de donnee */
#define S_INT8 "int8"
#define S_INT16 "int16"
#define S_INT32 "int32"
#define S_UINT8 "uint8"
#define S_UINT16 "uint16"
#define S_UINT32 "uint32"
#define S_STRING "string"
#define S_DOUBLE "double"
        
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
            short entierSigne2;
            int entierSigne4;

            /* entiers non signés */
            unsigned char entierNonSigne1;
            unsigned short entierNonSigne2;
            unsigned int entierNonSigne4;

            /* chaîne de caractères */
            struct chaine {
                    short taille;
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

/* Affichage d'une trame ou d'une donnee */
void afficher_trame(Trame trame);
void afficher_donnee(Donnee trame);

/* Ajout de donnees */
void ajouter_donnee(Trame* t, Donnee d);
void ajouter_donnees(Trame* t, Donnee* d);

#endif /* TRAME_H_ */
