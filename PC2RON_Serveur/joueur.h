/* 
 * File:   joueur.h
 * Author: mehdi
 *
 * Created on 10 décembre 2011, 18:17
 */

#ifndef JOUEUR_H
#define	JOUEUR_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* Coordonnees d'une position */
typedef struct Coord {
    uint16_t x;
    uint16_t y;
} Coord;

/* Composantes RVB d'une couleur */
typedef struct RGB {
    uint8_t r;
    uint8_t v;
    uint8_t b;
} RGB;

/* Vitesse en nombre de pas par centieme de seconde */
typedef enum Speed {
    SLOW = 3,
    NORMAL = 5,
    SPEED = 10,
    TURBO = 15,
} Speed;

/* 4 directions possibles */
typedef enum Direction {
    TOP = 1,
    BOTTOM = 2,
    LEFT = 3,
    RIGHT = 4
} Direction;

typedef struct Player {
    /* Identifiant unique du joueur */
    uint16_t id;
    
    /* Pseudo unique du joueur */
    char* name;

    /* Couleur de la moto en RVB */
    RGB color;

    /* Positions du joueur */
    struct positions {
        Coord* point;
        size_t size;
    } positions;

    /* Direction du joueur */ 
    Direction dir;

    /* Nombre de pas de grille en un centieme de seconde  */ 
    uint8_t speed;
    
    /* Nombre de pas effectues par le joueur */
    int nb_steps;
    
    /* Socket de donnexion */
    int sock;
    
    /* Etat d'inscription */
    int is_registered;
    
    /* Etat de connexion */
    int is_connected;
    
    /*  */
    int is_winner;
} *Player; 


/* Liste de joueurs representee dans une structure
 * afin de sauver le nombre de joueurs
 */
typedef struct Players {
    Player* player;
    size_t size;
} *Players;

/* Creation de joueurs */
Players create_the_players(size_t size);
Player create_player(void);

/* Recherche d'un joueur (par socket, id ou nom) */
Player get_player_by_id(uint16_t id, const Players the_players);
Player get_player_by_sock(int sock, const Players the_players);
Player get_player_by_name(const char* name, const Players the_players);

/* Modification de l'etat d'un joueur */
int register_player(int sock, uint16_t id, Players the_players);
void remove_player_by_id(uint16_t uid, Players the_players, int hard_remove);
void remove_player_by_sock(int sock, Players the_players, int hard_remove);

/* Recupereration de l'etat d'un joueur */
int is_registered(int sock, const Players the_players);
int is_connected(int sock, const Players the_players);

/* Contrainte sur l'unicite du nom de joueur */
int is_unique_name(const char* name, const Players the_players);

/* Compter le nombre de joueurs connectes ou inscrits */
int count_connected_players(const Players the_players);
int count_registered_players(const Players the_players);

#ifdef	__cplusplus
}
#endif

#endif	/* JOUEUR_H */

