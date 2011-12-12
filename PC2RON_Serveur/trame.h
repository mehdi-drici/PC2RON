/*
 * trame.h
 *
 *  Created on: 27 nov. 2011
 *      Author: Mehdi Drici
 */

#ifndef TRAME_H_
#define TRAME_H_

typedef int SOCKET;

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
#define S_END "END"

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

/* Libération de l'espace mémoire alloué à une trame et ses données */
void free_trame(Trame* t);

#endif /* TRAME_H_ */
