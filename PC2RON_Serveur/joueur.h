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

typedef struct Point {
    unsigned short x;
    unsigned short y;
} Point;

typedef struct RVB {
    unsigned char r;
    unsigned char v;
    unsigned char b;
} RVB;

typedef enum Vitesse {
    TRES_LENT = 3,
    LENT = 5,
    NORMAL = 10,
    RAPIDE = 15,
    TURBO = 20
} Vitesse;

typedef enum Direction {
    HAUT = 1,
    BAS = 2,
    GAUCHE = 3,
    DROITE = 4
} Direction;

typedef struct Joueur {
    unsigned short id;
    char* nom;

    /* Couleur */
    RVB couleur;

    /* Positions  */ 
    Point positions[0];

    /*   direction  */ 
    Direction dir;

    /* Nombre de pas de grille en un centieme de seconde  */ 
    unsigned char speed;
    
    int sock;
    int estInscrit;
    int estConnecte;
} *Joueur; 



typedef struct Joueurs {
    Joueur* joueur;
    size_t nbJoueurs;
    int nbMaxJoueurs;
} *Joueurs;

/*void init_joueur(int sock, Joueur j);*/
/*int ajouter_joueur(Joueurs lesJoueurs, Joueur j);*/
void init_joueurs(Joueurs lesJoueurs, size_t taille);
Joueur creer_joueur(void);
Joueur get_joueur_par_id(unsigned short id, Joueurs lesJoueurs);
Joueur get_joueur_par_sock(int sock, const Joueurs lesJoueurs);
void set_inscription_joueur(Joueur j, int booleen);
void set_connexion_joueur(Joueur j, int booleen);
int est_inscrit(const Joueur j);
int est_connecte(const Joueur j);
/*int get_max_joueurs(const Joueurs lesJoueurs);*/

#ifdef	__cplusplus
}
#endif

#endif	/* JOUEUR_H */

