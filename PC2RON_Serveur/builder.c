#include <stdio.h>
#include "builder.h"
#include "protocole.h"
#include "trame.h"
#include "factory.h"
#include "joueur.h"

/*
*******************************************************************************
 Author: Mehdi Drici

 File: builder.c
 
 Description: Constructeur des trames specifique au protocole PC2RON
              Ce pattern permet d'assurer une meille independance 
              de la couche transport
*******************************************************************************
*/

/**
 * Creation d'une trame Ack
 * Il s'agit d'un acquittement à la trame Initiate
 * @param boolean valeur de verite de l'acquittement
 * @return 
 */
Frame create_ack(int boolean) {
    Frame ack_frame = create_frame(Ack);
    
    Data ok = create_string("OK");
    Data no = create_string("NO");
    Data version = create_string(STR_VERSION);
    
    if(boolean) {
        add_data(ack_frame, ok); 
    } else {
        add_data(ack_frame, no);
    }
    
    add_data(ack_frame, version);
    
    return ack_frame;
}

/**
 * Creation d'une trame Registered
 * Il s'agit d'un acquittement positif à la trame Connect
 * @param uid identifiant du joueur
 * @return Trame Registered Ok
 */
Frame create_registered_ok(uint16_t uid) {
    Frame reg_frame = create_frame(Registered);
    Data ok = create_string("OK");
    Data id = create_uint16(uid);
    
    add_data(reg_frame, ok);
    add_data(reg_frame, id);
    
    return reg_frame;
}

/**
 * Creation d'une trame Registered
 * Il s'agit d'un acquittement negatif à la trame Connect
 * @param msg Message d'erreur d'inscription
 * @return Trame Registered No
 */
Frame create_registered_no(const char* msg) {
    Frame reg_frame = create_frame(Registered);
    Data no = create_string("NO");
    Data error = create_string(msg);
    
    add_data(reg_frame, no);
    add_data(reg_frame, error);
    
    return reg_frame;
}

/**
 * Creation de la trame User 
 * @param player Joueur dont les informations sont recuperees
 * @return Trame User
 */
Frame create_user(Player player) {
    Frame user_frame = create_frame(User);
    Data id = create_uint16(player->id);
    Data name = create_string(player->name);
    
    /* Creation des donnees representant la couleur */
    Data r = create_uint8(player->color.r);
    Data g = create_uint8(player->color.v);
    Data b = create_uint8(player->color.b);
    
    /* Creation des donnees representant la position initiale du joueur
     * @todo modifier pour la derniere position
    */
    Data x0 = create_uint16(player->positions.point[0].x);
    Data y0 = create_uint16(player->positions.point[0].y);
    
    Data dir = create_uint8(player->dir);
    Data speed = create_uint8(player->speed);
    
    /* Ajout des donnees a la trame User */
    add_data(user_frame, id);
    add_data(user_frame, name);
    
    add_data(user_frame, r);
    add_data(user_frame, g);
    add_data(user_frame, b);
    
    add_data(user_frame, x0);
    add_data(user_frame, y0);
    add_data(user_frame, dir);
    add_data(user_frame, speed);
    
    return user_frame;
}

/**
 * Creation de la trame Win
 * @param id Identifant du joueur gagnant
 * @return Trame Win
 */
Frame create_win(uint16_t uid) {
    Frame win_frame = create_frame(Win);
    
    Data id = create_uint16(uid);
    add_data(win_frame, id);
    
    return win_frame;
}

   /*   Un participant meurt  */ 
/**
 * Creation d'une trame Death contenant l'id du joueur mort
 * @param uid Identifiant d'un joueur perdant
 * @return Trame Death
 */
Frame create_death(uint16_t uid) {
    Frame death_frame = create_frame(Death);

    Data id = create_uint16(uid);
    add_data(death_frame, id);
    
    return death_frame;    
}

/**
 * Creation d'une trame Death contenant les ids des 2 survivants
 * @param uid1 Identifiant du joueur survivant 1 
 * @param uid2 Identifiant du joueur survivant 2
 * @return Trame Death
 */
Frame create_two_deaths(uint16_t uid1, uint16_t uid2) {
    Frame death_frame = create_frame(Death);
    Data id;
    
    /* Creation des identifiants des survivants */
    id = create_uint16(uid1);
    add_data(death_frame, id);
    
    id = create_uint16(uid2);
    add_data(death_frame, id);

    return death_frame;    
}

/**
 * Creation d'une trame Pause
 * @param msg Message de pause
 * @return Trame Pause
 */
Frame create_pause(const char* msg) {
    Frame pause_frame = create_frame(Pause);
    Data pause_msg = create_string(msg);
    add_data(pause_frame, pause_msg);
    
    return pause_frame;
}

/**
 * Creation d'une trame Start
 * @param msg Message de Start
 * @return Trame Start
 */
Frame create_start(const char* msg) {
    Frame FrameStart = create_frame(Start);
    Data start_msg = create_string(msg);
    add_data(FrameStart, start_msg);
    
    return FrameStart;
}

/**
 * Creation d'une trame Turn
 * Il s'agit d'une mise a jour des positions et directions pour les joueurs
 * @param time Temps ecoule depuis le debut de la partie
 * @param lesJoueurs
 * @return Trame Turn 
 */ 
Frame create_turn(uint32_t time, Players the_players) {
    Frame turn_frame = create_frame(Turn);
    Data id, x, y, dir, elapsed_time;
    size_t i;
    size_t nb_positions = 0;
    Player current_player;
    
    /* Creation de la donnee representant le temps ecoule */
    elapsed_time = create_uint32(time);
    add_data(turn_frame, elapsed_time);
    
    /* Creation des donnees representant 
     * les positions et directions des joueurs
     */
    for(i=0; i < the_players->size; i++) {
        current_player = the_players->player[i];
        
        /* Seuls les joueurs encore vivants sont pris en compte*/
        if(current_player->is_registered) {
            nb_positions = current_player->positions.size;

            id = create_uint16(current_player->id);
            x = create_uint16(current_player->positions.point[nb_positions-1].x);
            y = create_uint16(current_player->positions.point[nb_positions-1].y);
            dir = create_uint16(current_player->dir);

            add_data(turn_frame, id);
            add_data(turn_frame, x);
            add_data(turn_frame, y);
            add_data(turn_frame, dir);
        }
    }
    
    return turn_frame;
}

/**
 * Creation d'une trame de fin
 * Dans la version de base, elle correspond a la fin de la liste des joueurs
 * @return Trame End
 */
Frame create_end() {
    return create_frame(End);
}