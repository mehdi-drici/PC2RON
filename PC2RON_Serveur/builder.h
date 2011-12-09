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
#include "factory.h"
    
//typedef enum {false, true} bool;

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
} Joueur; 

typedef enum TypeTrame {
	Ack = 0x41,
	Connect = 0x43,
        Death = 0x44,
	End = 0x45,
	Initiate = 0x49,
        Order = 0x4F,
	Pause = 0x50,
	Registered = 0x52,
	Start = 0x53,
	User = 0x55,
        Turn = 0x54,
        Win = 0x57
} TypeTrame;

Trame creer_trame_ack(int ok);
Trame creer_trame_registered_ok(unsigned short id);
Trame creer_trame_registered_no(char* message);
Trame creer_trame_user(Joueur j);
Trame creer_trame_win(unsigned short id);
Trame creer_trame_death(unsigned short id[]);
Trame creer_trame_pause(char* message);
Trame creer_trame_start(char* message);
Trame creer_trame_turn(unsigned int t, Joueur j[]);
Trame creer_trame_end();
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUILDER_H */

