/* 
 * File:   joueur.h
 * Author: mehdi
 *
 * Created on 10 décembre 2011, 18:17
 */

#ifndef JOUEUR_H
#define	JOUEUR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NB_MAX_JOUEURS 3
extern typedef int SOCKET ;

typedef enum Direction {
    HAUT = 1,
    BAS = 2,
    GAUCHE = 3,
    DROITE = 4
} Direction;

typedef struct Joueur {
    unsigned short id;
    char* nom;

    // Couleur
    unsigned char r;
    unsigned char v;
    unsigned char b;

    // Positions
    unsigned short x;
    unsigned short y;

    // direction
    //unsigned short dir;
    Direction dir;

    // Nombre de pas de grille en un centieme de seconde
    unsigned char speed;
    
    SOCKET sock;
    int estInscrit;
    int estConnecte;
} Joueur; 

void init_joueur(SOCKET sock, Joueur* j);
Joueur* get_joueur(SOCKET sock, Joueur joueurs[]);
int set_inscription_joueur(SOCKET sock, int booleen);
int set_connexion_joueur(SOCKET sock, int booleen);

#ifdef	__cplusplus
}
#endif

#endif	/* JOUEUR_H */

