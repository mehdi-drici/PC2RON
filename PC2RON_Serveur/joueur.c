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
 * Creation d'un joueur
 * @return Le joueur cree
 */
Player create_player() {
    Player player_created = malloc(sizeof(struct Player));
    
    player_created->sock = -1;
    
    player_created->name = NULL;
    player_created->dir = TOP;
    player_created->id = 0;
    
    /* Initialisation de la position du joueur 
     * @todo position aleatoire
     */
    player_created->positions.point = malloc(sizeof(Coord));
    player_created->positions.point[0].x = 0;
    player_created->positions.point[0].y = 0;
    
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
        
        printf("current_player->name = %s\n", current_player->name);
        printf("name = %s\n", name);
        
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