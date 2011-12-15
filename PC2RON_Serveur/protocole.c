#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocole.h"
#include "erreur.h"
#include "builder.h"
#include "reception.h"
#include "envoi.h"
#include "factory.h"

/*
*******************************************************************************
 Author: Mehdi Drici

 File: protocole.c
 
 Description: Protocole de la couche application (PC2RON)
 Il gere l'echange avec un client et permet d'assurer 
 la coherence de cet echange.
 
 Il dispose pour cela de:
 - envoi de message aux joueurs
 - traitement des requetes
 - Validation des contraintes du protocole (format des trames et coherence du jeu) 
*******************************************************************************
*/

/**
 * Verifier le nom d'application
 * @param appname Nom de l'application a verifier
 * @return SUCCESS(1) si le nom d'application est correct, ERROR(0) sinon
 */
int check_appname(char* appname) {
    int check = ERROR;
    
    /* Suppression du '?' du champ application de la requete */ 
    appname[strlen(appname) - 1] = '\0';
    
    if(strcmp(appname, STR_APPLI) != 0) {
        PRINT_WRONG_APPNAME(appname);
    } else {
        check = SUCCESS;
    }
    
    return check;
}

/**
 * Verifier le nom de version du protocole
 * @param version Nom de la version a verifier
 * @return SUCCESS(1) si le nom de version est correct, ERROR(0) sinon
 */
int check_version(const char* version) {
    int check = ERROR;
    
    if(strcmp(version, STR_VERSION) != 0) {
            PRINT_UNSUPPORTED_VERSION(version);
    } else {
        check = SUCCESS;
    }
    
    return check;
}

/**
 * Verifier une trame
 * @param frame Trame a verifier
 * @return SUCCESS(1) si la trame est correcte, ERROR(0) sinon
 */
int check_frame(Frame frame) {
    if(frame == NULL) {
        return ERROR;
    } else {
        return SUCCESS;
    }
}

/**
 * Verifier le format d'une trame Connect
 * @param frame Trame Connect a verifier
 * @return NULL si la trame est correcte, un message d'erreur sinon
 */
const char* check_connect_format(Frame frame) {
    const char* error_msg = NULL;
    
    if(frame->size != 4) {
        error_msg = STR_WRONG_FRAME_FORMAT;
        
    } else if(frame->data[0]->type != UINT8 ||
              frame->data[1]->type != UINT8 ||
              frame->data[2]->type != UINT8) {
        error_msg = STR_WRONG_RGB_FORMAT;
        
    } else if(frame->data[3]->type != STRING) {
        error_msg = STR_WRONG_NAME_FORMAT;
    } 
    
    return error_msg;
}

/**
 * Verifier le format d'une trame Initiate
 * @param frame Trame Initiate a verifier
 * @return SUCCESS(1) si le format est correct, ERROR(0) sinon
 */
int check_initiate_format(Frame frame) {
    int check = ERROR;
    
    if(frame->size != 2) {
        PRINT_WRONG_DATA_SIZE(STR_INITIATE);
        
    } else if(frame->data[0]->type != STRING ||
              frame->data[1]->type != STRING) {
        PRINT_WRONG_FORMAT(STR_INITIATE);
        
    } else {
        check = SUCCESS;
    }
   
    return check;
}      

/**
 * Verifier le format d'une trame Order
 * @param frame Trame Order a verifier
 * @return SUCCESS(1) si le format est correct, ERROR(0) sinon
 */
int check_order_format(Frame frame) {
    int check = ERROR;
    
    if(frame->size == 1 &&
       frame->data[0]->type == STRING) {
        check = SUCCESS;
        
    } else {
        check = SUCCESS;
    }
     
    return check;
}

/**
 * Verification du respect des contraintes d'une trame Connect:
 * - le joueur doit etre connecte
 * 
 * @param sock Socket du joueur ayant envoye cette trame
 * @param the_players Liste des joueurs ou s'effectue la verification
 * @return NULL si les contraintes sont respectees, un message d'erreur sinon
 */
const char* check_connect_constraint(int sock, Players the_players) {
    const char* error_msg = NULL;
    
    /* Verification de la connexion du joueur */
    if(!is_connected(sock, the_players)) {
        error_msg = STR_NOT_CONNECTED;
    }
    
    return error_msg;
}

/**
 * Verification du respect des contraintes d'une trame Order:
 * - le joueur doit etre inscrit
 * 
 * @param sock Socket du joueur ayant envoye cette trame
 * @param the_players Liste des joueurs ou s'effectue la verification
 * @return SUCCESS(1) si les contraintes sont respectees, ERROR(0) sinon
 */
int check_order_constraint(int sock, Players the_players) {
    int check = ERROR;
    
    check = is_registered(sock, the_players);
    
    return check;
}

/* Quota de joueurs non atteint */
/**
 * Verification du respect des contraintes d'une trame Initiate:
 * - le joueur ne doit pas etre inscrit
 * - le quota de joueurs ne doit pas etre depasse 
 * 
 * @param sock Socket du joueur ayant envoye cette trame
 * @param the_players Liste des joueurs ou s'effectue la verification
 * @return SUCCESS(1) si les contraintes sont respectees, ERROR(0) sinon
 */
int check_initiate_constraint(int sock, size_t nb_connected_players, Players the_players) {
    
    Player player = get_player_by_sock(sock, the_players);
    int check = ERROR;
    
    if (is_connected(sock, the_players)) {
        PRINT_ALREADY_CONNECTED(player->sock);
        
    } else if(nb_connected_players >= the_players->size) {
        PRINT_LIMIT_PLAYERS_CONNECTED_REACHED();
        
    } else {
        check = SUCCESS;
    }
    
    return check;
}

/**
 * Repondre a une requete d'un joueur
 * NOTA: cette fonction est bloquante et attend une requete d'un joueur 
 * 
 * @param sock Socket du joueur ayant envoye une requete
 * @param the_players Liste des joueurs
 * @return Resultat de l'echange compose de 2 champs:
 *         - type: correspond le plus souvent au type de trame
 *                 ou a une fin de connexion
 *         - content: correspond au contenu brut de l'echange, a savoir
 *                    une structure Player, un identifiant ou un ordre.
 */
Result* respond(int sock, Players the_players) {
    Result* result = NULL;
    Frame frame = recv_frame(sock);
    
    if(check_frame(frame) == SUCCESS) {
        
        /* Deconnexion du joueur */
        if(frame->pennant == SPECIAL_FRAME) {
            result = malloc(sizeof(Result));
            remove_player_by_sock(sock, the_players, 1);
            
            result->type = NOT_CONNECTED;
            result->content = NULL;
        
        /* Traitement du serveur a la requete du client */
        } else {
            switch(frame->id) {      
                case Connect:
                    result = respond_connect(sock, the_players, frame);
                    break;

                case Initiate:
                    result = respond_initiate(sock, the_players, frame);
                    break;

                case Order:
                    result = respond_order(sock, the_players, frame);
                    break;
                
                /* Type de trame inconnu ou non autorisee du protocole 
                 * @todo si type de trame existant, renvoyer une erreur specifique
                 */
                default:
                    PRINT_UNKNOWN_FRAME_TYPE(frame->id);
                    break;
            }
        }
    }
    
    if(frame != NULL) {
        free_frame(frame);
    }
    
    return result;
}

/**
 * Repondre a une requete Initiate
 * @param sock Socket du joueur ayant envoye une demande de connexion
 * @param the_players Liste des joueurs
 * @param recv_frame Trame Initiate recue
 * @return Resultat de l'echange (cf. fonction respond pour plus d'informations)
 */
Result* respond_initiate(int sock, Players the_players, Frame frame) {
    /* Compteur persistant de joueurs connectes */
    static uint16_t nb_connected_players = 0;
    
    /* Resultat de l'echange */
    Result* result = NULL;
    
    /* Acquittement de la requete, negatif par defaut  */ 
    Frame ack_frame = create_ack(0);
    
    /* Verification de la requete du client */
    int format_check = ERROR;
    int constraint_check = ERROR;
    
    constraint_check = check_initiate_constraint(sock, nb_connected_players, the_players);
    format_check = check_initiate_format(frame);
    
    /* Traitement de la requete */
    if(constraint_check == SUCCESS && 
           format_check == SUCCESS) {
        
        /* Verification du nom d'application et de la version du protocole */
        if(check_appname(frame->data[0]->string.content) == SUCCESS &&
           check_version(frame->data[1]->string.content) == SUCCESS) {
            
            /* Creation du resultat de l'echange */
            result = malloc(sizeof(Result));
            result->type = Initiate;
            result->content = NULL;
            
            /* Connexion du nouveau joueur */
            the_players->player[nb_connected_players]->sock = sock;
            the_players->player[nb_connected_players]->is_connected = 1;
            
            nb_connected_players++;
            free_frame(ack_frame);
            ack_frame = create_ack(1);
        }
    }
    
    /* Envoi de l'acquittement */
    send_frame(sock, ack_frame);
    
    return result;
}

/**
 * Repondre a une requete Connect
 * @param sock Socket du joueur ayant envoye une demande d'inscription
 * @param the_players Liste des joueurs
 * @param recv_frame Trame Connect recue
 * @return Resultat de l'echange (cf. fonction respond pour plus d'informations)
 */
Result* respond_connect(int sock, Players the_players, Frame frame) {
    /* Compteur persistant de joueurs inscrits */
    static uint16_t nb_registered_players = 0;
    
    Result* result = NULL;
    Frame reg_frame;
    Player player;
    
    /* Verification de la requete du client */
    const char* format_check = NULL;
    const char* constraint_check = NULL;
    
    /* Verification des erreurs */
    constraint_check = check_connect_constraint(sock, the_players);
    format_check = check_connect_format(frame); 
    
    if(format_check != NULL) {
        reg_frame = create_registered_no(format_check);
        
    } else if (constraint_check != NULL) {
        reg_frame = create_registered_no(constraint_check);
    
    /* Inscription du nouveau joueur */
    } else {
        nb_registered_players++;
        
        /* Initialisation des infos du joueur */
        player = get_player_by_sock(sock, the_players);
        player->is_registered = 1;
        player->color.r = frame->data[0]->uint8;
        player->color.v = frame->data[1]->uint8;
        player->color.b = frame->data[2]->uint8;
        
        if(is_unique_name(frame->data[3]->string.content, the_players)) {
            player->name = frame->data[3]->string.content;
        } else {
            int i = 0;
            char* old_name = frame->data[3]->string.content;
            char* new_name = malloc(frame->data[3]->string.size + (size_t)3);
            /*strcat(new_name, "_1");*/
            
            while(!is_unique_name(new_name, the_players)) {
                printf("%s\n", new_name);
                sprintf(new_name, "%s_%d", old_name, i);
                i++;
            }

            player->name = new_name;
        }
        
        player->id = nb_registered_players;
        
        /* Creation du resultat de l'echange */
        result = malloc(sizeof(Result));
        result->type = Connect;
        result->content = player;
        
        reg_frame = create_registered_ok(player->id);
    }
    
    send_frame(sock, reg_frame);
    
    return result;
}

/**
 * Repondre a une requete Order
 * @param sock Socket du joueur ayant envoye un ordre
 * @param the_players Liste des joueurs
 * @param recv_frame Trame Order recue
 * @return Resultat de l'echange (cf. fonction respond pour plus d'informations)
 */
Result* respond_order(int sock, Players the_players, Frame frame) {
    Result* result = NULL;
    
    if (check_order_format(frame) == SUCCESS &&
        check_order_constraint(sock, the_players) == SUCCESS) {
        
        /* Creation du resultat de l'echange */
        result = malloc(sizeof(Result));
        result->type = Order;
        result->content = frame->data[0]->string.content;
    }
    
    return result;
}

/**
 * Envoi d'une trame a tous les joueurs encore connectes (broadcast)
 * S'il y'a un probleme d'envoi, le joueur concerne est deconnecte et desinscrit
 * 
 * @param the_players Liste des joueurs
 * @param frame Trame a envoyer
 */
void send_broadcast(Players the_players, Frame frame) {
    size_t i = 0;
    Player current_player;
    
    for(i=0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        
        /* Envoi de la trame a tous les joueurs inscrits 
         * Desinscription et deconnexion du joueur en cas de deconnexion brutale 
         */
        if(current_player->is_registered) {
            if(send_frame(current_player->sock, frame) == ERROR) {
                remove_player_by_sock(current_player->sock, the_players, 1);
            }
        }
    }
     
    free_frame(frame);
}

/*
 * Envoi d'un message Pause a tous les joueurs encore connectes (broadcast)
 * @param the_players Liste des joueurs
 * @param msg Message a envoyer
 */
void send_pause(Players the_players, const char* msg) {
    Frame pause_frame = create_pause(msg);
    send_broadcast(the_players, pause_frame);
}

/*
 * Envoi d'un message Start a tous les joueurs encore connectes (broadcast)
 * @param the_players Liste des joueurs
 * @param msg Message a envoyer
 */
void send_start(Players the_players, const char* msg) {
    Frame start_frame = create_start(msg);
    send_broadcast(the_players, start_frame);    
}

/*
 * Envoi de la liste des joueurs en broadcast
 * @param the_players Liste des joueurs
 */
void send_user(Players the_players) {
    size_t i = 0;
    Frame user_frame;
    Player current_player;
    
    /* Envoi a tous les clients de la trame User 
     * qui decrit chaque joueur connecte */
    for(i=0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        
        if(current_player->is_connected) {
            user_frame = create_user(current_player);
            send_broadcast(the_players, user_frame);
        }
    }
    
    /* Fin de la liste de joueurs */
    send_end(the_players);
}

/**
 * Envoi des positions et directions de tous les participants
 * encore vivants en broadcast
 * 
 * @param the_players Liste des joueurs
 * @param elapsed_time Temps ecoule depuis le debut de la partie
 */
void send_turn(Players the_players, uint32_t elapsed_time) {
    Frame turn_frame = create_turn(elapsed_time, the_players); 
    send_broadcast(the_players, turn_frame);
}

/**
 * Envoi de la trame End precisant la fin de la liste des joueurs
 * @param the_players Liste des joueurs
 */
void send_end(Players the_players) {
    Frame end_frame = create_end();
    send_broadcast(the_players, end_frame);
}

/**
 * Envoi du gagnant a tous les participants
 * @param the_players Liste des joueurs
 * @param uid Identifiant du gagnant
 */
void send_win(Players the_players, uint16_t uid) {
    Player winner = get_player_by_id(uid, the_players);
    Frame win_frame = create_win(uid);
    send_broadcast(the_players, win_frame);
    
    /* Changement de statut du gagnant */
    winner->is_winner = 1;
    
    /* Desinscription du gagnant */
    remove_player_by_id(uid, the_players, 0);
}

/**
 * Envoi du gagnant a tous les participants
 * @param the_players Liste des joueurs
 * @param uid Identifiant du gagnant
 */
void send_death(Players the_players, uint16_t uid) {
    Frame death_frame = create_death(uid);
    send_broadcast(the_players, death_frame);
    
    /* Desinscription du perdant */
    remove_player_by_id(uid, the_players, 0);
}

/**
 * Envoi de la trame Death contenant les 2 perdants en broadcast
 * @param the_players Liste des joueurs
 * @param uid1 Identifiant d'un survivant mort
 * @param uid2 Identifiant d'un survivant mort
 */
void send_two_deaths(Players the_players, uint16_t uid1, uint16_t uid2) {
    Frame death_frame = create_two_deaths(uid1, uid2);
    send_broadcast(the_players, death_frame);
    
    /* Desinscription des perdants */
    remove_player_by_id(uid1, the_players, 0);
    remove_player_by_id(uid2, the_players, 0);    
}