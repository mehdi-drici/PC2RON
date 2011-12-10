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
    
    int sock;
    int estInscrit;
    int estConnecte;
} Joueur; 

typedef struct Joueurs {
    Joueur* joueur;
    int nbJoueurs;
} Joueurs;

void init_joueur(int sock, Joueur* j);
Joueur* get_joueur(int sock, const Joueurs lesJoueurs);
int set_inscription_joueur(Joueur* j, int booleen);
int set_connexion_joueur(Joueur* j, int booleen);
int est_inscrit(const Joueur j);
int est_connecte(const Joueur j);

#ifdef	__cplusplus
}
#endif

#endif	/* JOUEUR_H */

