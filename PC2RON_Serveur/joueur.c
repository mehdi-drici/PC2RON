#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joueur.h"
#include "erreur.h"

/*
*******************************************************************************
 Author: Mehdi Drici

 File: player.c
 
 Description: Gestion d'un joueur:
              - ajout et suppression de joueurs
              - recherche d'un joueur
              - connexion et inscription d'un joueur
              - verification de la contrainte de l'unicite du nom
*******************************************************************************
*/

/**
 * Creation d'une liste de joueurs
 * @param size Nombre de joueurs a creer
 * @return Liste des joueurs crees
 */
Players create_the_players(size_t size) {
    Players the_players;
    size_t i = 0;
    
    /* Initialisation du nombre de joueurs */
    the_players = malloc(sizeof(struct Players));
    the_players->size = size;
    the_players->player = calloc(size, sizeof(struct Player));
    
    /* Creation des joueurs */
    for(i=0; i < the_players->size; i++) {
        the_players->player[i] = create_player();
    }
    
    return the_players;
}

/**
 * Creation et initialisation d'un joueur
 * @return Le joueur cree
 */
Player create_player() {
    Player player_created = malloc(sizeof(struct Player));
    
    player_created->sock = -1;
    
    player_created->name = NULL;
    player_created->dir = RIGHT;
    player_created->id = 0;
    
    /* Initialisation de la position du joueur 
     * @todo position aleatoire
     */
    player_created->positions.size = 1;
    player_created->positions.point = malloc(sizeof(Coord));
    player_created->positions.point[0].x = 50;
    player_created->positions.point[0].y = 50;
    
    /* Initialisation de la couleur RGB du joueur */
    player_created->color.r = 0;
    player_created->color.v = 0;
    player_created->color.b = 0;
    
    player_created->speed = SLOW;
    player_created->is_winner = 0;
    
    /* A l'initialisation, le joueur n'est ni connecte, ni inscrit */
    player_created->is_connected = 0;
    player_created->is_registered = 0;
    
    return player_created;
}

/**
 * Recuperation d'un joueur a partir de sa socket (qui est unique) 
 * @param sock Socket de connexion du joueur a rechercher
 * @param Liste des joueurs ou s'effectue la recherche 
 * @return Le joueur trouve si succes, NULL sinon
 */
Player get_player_by_sock(int sock, const Players the_players) {
    size_t i = 0;
    
    while (i < the_players->size) {
        if(the_players->player[i]->sock == sock) {
            return the_players->player[i];
        }
        
        i++;
    }
    
    return NULL;
}

/**
 * Recuperation d'un joueur a partir de son id (qui est unique) 
 * @param uid Identifiant du joueur a rechercher
 * @param the_players Liste des joueurs ou s'effectue la recherche 
 * @return Le joueur trouve si succes, NULL sinon
 */
Player get_player_by_id(uint16_t uid, const Players the_players) {
    size_t i = 0;
    
    while (i < the_players->size) {
        if(the_players->player[i]->id == uid) {
            return the_players->player[i];
        }
        
        i++;
    }
    
    return NULL;
}


/**
 * Recuperation d'un joueur a partir de son id (qui est unique) 
 * @param name Nom du joueur a rechercher
 * @param the_players Liste des joueurs ou s'effectue la recherche 
 * @return Le joueur trouve si succes, NULL sinon
 */
Player get_player_by_name(const char* name, const Players the_players) {
    size_t i = 0;
    Player current_player;
    
    while (i < the_players->size) {
        current_player = the_players->player[i];
        
        if(current_player->name != NULL && 
           0 == strcmp(current_player->name, name)) {
            return the_players->player[i];
        }
        
        i++;
    }
    
    return NULL;
}

/**
 * Desinscription (et deconnexion optionnelle) d'un joueur
 * Ce dernier reste toujours connecte
 * @param uid Identifiant du joueur a retirer
 * @param the_players Liste des joueurs ou se situe le joueur
 * @param hard_remove booleen indiquant s'il faut deconnecter le joueur
 */
void remove_player_by_id(uint16_t uid, Players the_players, int hard_remove) {
    Player player_removed = get_player_by_id(uid, the_players);
    
    if(player_removed != NULL) {
        remove_player_by_sock(player_removed->sock, the_players, hard_remove);
    }
}

/**
 * Desinscription (et deconnexion optionnelle) d'un joueur
 * @param sock Socket du joueur a retirer
 * @param the_players Liste des joueurs ou se situe le joueur
 * @param hard booleen indiquant s'il faut deconnecter le joueur
 */
void remove_player_by_sock(int sock, Players the_players, int hard_remove) {
    Player player_removed = get_player_by_sock(sock, the_players);
    
    if(player_removed != NULL) {
        /* Desincription du joueur */
        player_removed->is_registered = 0;
        player_removed->sock = -1;
        player_removed->id = 0;
        
        /* Deconnexion optionnelle du joueur */
        if(hard_remove) {
            player_removed->is_connected = 0;
        }

        /* Liberation de l'espace memoire alloue */
        free(player_removed->positions.point);
    }
}

/**
 * Inscription d'un joueur
 * @param sock Socket de connexion
 * @param uid Identifiant du joueur a inscrire
 * @param the_players Liste des joueurs ou se situe le joueur
 * @return SUCCES(0) si l'inscription s'est correctement deroulee,
 *         ERROR(-1) sinon
 */
int register_player(int sock, uint16_t uid, Players the_players) {
    Player player_registered = get_player_by_sock(sock, the_players);
    
    if(player_registered != NULL) {
        player_registered->id = uid;
        return SUCCESS;
    }
    
    return ERROR;
}


/**
 * Etat de l'inscription du joueur (inscrit ou non inscrit)
 * @param sock Socket de connexion
 * @param the_players Liste des joueurs ou s'effectue la recherche
 * @return TRUE(1) si le joueur est inscrit, FALSE(0) sinon
 */
int is_registered(int sock, const Players the_players) {
    Player player_found = get_player_by_sock(sock, the_players);
    
    /* Le joueur ne s'est pas encore connecte */
    if(player_found == NULL) {
        return 0;
    }
    return player_found->is_registered;
}

/**
 * Etat de connexion du joueur (connecte ou deconnecte)
 * @param sock Socket de connexion
 * @param the_players Liste des joueurs ou s'effectue la recherche
 * @return TRUE(1) si le joueur est inscrit, FALSE(0) sinon
 */
int is_connected(int sock, const Players the_players) {
    Player player_found = get_player_by_sock(sock, the_players);
    
    /* Le joueur ne s'est pas encore connecte */
    if(player_found == NULL) {
        return 0;
    }
    return player_found->is_connected;
}

/**
 * Verification de l'unicite d'un nom de joueur
 * @param name Nom de joueur dont l'unicite est a verifier
 * @param the_players Liste des joueurs ou s'effectue la recherche
 * @return TRUE(1) si le joueur est unique, FALSE(0) sinon
 */
int is_unique_name(const char* name, const Players the_players) {
    Player player_found = get_player_by_name(name, the_players);
    
    /* Le nom est unique */
    if(player_found == NULL) {
        return 1;
    }
    
    return 0;
}

/**
 * Compter le nombre de joueurs inscrits
 * @param the_players Liste de joueurs ou s'effectue le comptage
 * @return nombre de joueurs inscrits
 */
int count_registered_players(const Players the_players) {
    size_t i = 0;
    int registered_counter = 0;
    Player current_player;
    
    for(i = 0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        
        if(current_player->is_registered) {
            registered_counter++;
        }
    }
    
    return registered_counter;
}

/**
 * Compter le nombre de joueurs connectes
 * @param the_players Liste de joueurs ou s'effectue le comptage
 * @return nombre de joueurs connectes
 */
int count_connected_players(const Players the_players) {
    size_t i = 0;
    int connected_counter = 0;
    Player current_player;
    
    for(i = 0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        
        if(current_player->is_connected) {
            connected_counter++;
        }
    }
    
    return connected_counter;
}

/**
 * Renommer un nom s'il existe deja
 * @param name Nom dont l'unicite est a verifier
 * @param name_size Taille du nom
 * @param the_players Liste de joueurs ou s'effectue la verification
 * @return Nouveau nom si le renommage a ete effectue
 */
char* rename_if_not_unique(char* name, size_t name_size, Players the_players) {
    size_t sizeof_suffix = 2;
    
    char* new_name;
    int i = 1;
    
    if(is_unique_name(name, the_players)) {
        return name;
    } 

    new_name = malloc(name_size + sizeof_suffix);

    do {
        printf("%s\n", new_name);
        sprintf(new_name, "%s_%d", name, i);
        i++;
    } while(!is_unique_name(new_name, the_players));

    
    return new_name;
}

/**
 * Mise a jour des positions des joueurs
 * en fonction de leur direction et de leur precedente position
 * Le nombre de positions ajoutees se fait en fonction de la vitesse du joueur
 * 
 * NOTA: Le repere graphique choisi est le meme que celui de Java
 *       A savoir l'axe des ordonnees vers le bas
 *       et l'axe des abscisses vers la droite
 * @param the_players Liste de joueurs
 */
void update_positions(Players the_players) {
    size_t i, j;
    
    Player current_player;
    Coord new_position;
    Coord old_position;
    size_t size;
    Speed speed;
    
    for(i = 0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        size = current_player->positions.size;
        old_position = current_player->positions.point[size-1];
        speed = current_player->speed;
        
        /* Initialisation de la nouvelle position */
        new_position.x = old_position.x;
        new_position.y = old_position.y;
        
        switch(current_player->dir) {
            case TOP:
                /* Ajout d'un nombre de positions proportionnel a la vitesse */
                for(j = 0; j < speed; j++) {
                    new_position.y--;
                    /*add_position(current_player, new_position);*/
                }
                break;
            
            case BOTTOM:
                for(j = 0; j < speed; j++) {
                    new_position.y++;
                    /*add_position(current_player, new_position);*/
                }
                break;
                
            case LEFT:
                for(j = 0; j < speed; j++) {
                    new_position.x--;
                    /*add_position(current_player, new_position);*/
                }
                break;
                
            case RIGHT:
                for(j = 0; j < speed; j++) {
                    new_position.x++;
                    add_position(current_player, new_position);
                }
                break;
        }
    }
}

/**
 * Ajouter une position a un joueur
 * @param player Le joueur dont on s'interesse
 * @param coord Les coordonnees de la nouvelle position
 */
void add_position(Player player, Coord coord) {
    /*size_t size = player->positions.size;*/
    Coord* positions = player->positions.point;
    
    /* Reallocation memoire pour une nouvelle position */
    /*positions = realloc(positions, 300 * sizeof(Coord));*/
    
    /* Ajout de la nouvelle position */
    /*positions[size] = coord;*/
    positions[0] = coord;
    
    /* Mise a jour de la taille */
    /*player->positions.size = size + 1;*/
}

/**
 * Recuperer l'identifiant du joueur en collision avec un engin
 * @param the_players Liste de joueurs
 * @return L'id du joueur en cas de collision, 0 sinon
 *         (l'identifiant d'un joueur etant strictement superieur a zero)
 */
uint16_t get_id_collision(Players the_players) {
    int collision = 0;
    Player player1, player2;
    size_t i = 0;
    size_t j = 0;
    
    while(!collision && i < the_players->size) {
        player1 = the_players->player[i];

        while(!collision && j < the_players->size) {
            player2 = the_players->player[j];

            collision = is_collision(player1, player2);
        }
    }
    
    if(collision) {
        return player1->id;
    } else {
        return 0;
    }
}

/**
 * Detection d'une collision entre deux joueurs
 * @param player1 Joueur a tester 
 * @param player2 Joueur a comparer
 * @return TRUE(1) si le joueur est inscrit, FALSE(0) sinon
 */
int is_collision(Player player1, Player player2) {
    int collision = 0;
    size_t i = 0;
    size_t j = 0;
    Coord current_position1;
    Coord current_position2;
    size_t size;
    
    /* En cas de verification de collision avec soi meme
     * (avec son mur d'energie)
     * on ne compare pas les dernieres positions
     */
    size = player2->positions.size;
    if(player1->id == player2->id) {
        size -= player2->speed;
    }
    
    /* Recherche de la presence d'une collision du player 1 avec le player 2
     * Seules les dernieres positions du player1 sont prises compte
     * car elles correspondent a la tete de l'engin
     */
    while(!collision && i < player1->positions.size && i < player1->speed) {
        current_position1 = player1->positions.point[i];
        
        while(!collision && j < size) {
            current_position2 = player2->positions.point[j];

            /* Detection d'une collision */
            if(current_position1.x == current_position2.x &&
               current_position1.y == current_position2.y) {
                collision = 1;
            }
        }
    }
    
    return collision;
}