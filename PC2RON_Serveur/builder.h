/* 
 * File:   builder.h
 * Author: mehdi
 *
 * Created on 8 décembre 2011, 18:05
 */

#ifndef BUILDER_H
#define	BUILDER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"
    
//typedef enum {false, true} bool;

typedef enum Ordre {
    droit = "idle",
    gauche = "left",
    droite = "right",
    abandon = "abandon"
} Ordre;

typedef enum Direction {
    haut = 1,
    bas = 2,
    gauche = 3,
    droite = 4
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
} Joueur; 

Trame creer_trame_ack(bool ok);
Trame creer_trame_registered_ok(unsigned short id);
Trame creer_trame_registered_no(char* message);
Trame creer_trame_user(Joueur j);
Trame creer_trame_win(int id);
Trame creer_trame_death(unsigned short id[]);
Trame creer_trame_pause(char* message);
Trame creer_trame_start(char* message);
Trame creer_trame_turn(unsigned int t, Joueur j[]);
Trame creer_trame_end();
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUILDER_H */

