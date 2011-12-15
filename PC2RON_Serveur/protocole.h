/*
 * protocole.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#define STR_APPLI "PC2RON"
#define STR_VERSION "PC2RON2011"

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define NOT_CONNECTED -1

#include "joueur.h"
#include "trame.h"

/* Chaines de caracteres correspondant aux types de donnee */
#define STR_ACK "ACK"
#define STR_CONNECT "CONNECT"
#define STR_DEATH "DEATH"
#define STR_END_OF_LIST "END OF LIST"
#define STR_INITIATE "INITIATE"
#define STR_ORDER "ORDER"
#define STR_PAUSE "PAUSE"
#define STR_REGISTERED "REGISTERED"
#define STR_START "START"
#define STR_USER "USER"
#define STR_TURN "TURN"
#define STR_WIN "WIN"

/* Ordres */ 
#define STRAIGHT_ORDER "idle"
#define LEFT_ORDER "left"
#define RIGHT_ORDER "right"
#define ABORT_ORDER "abandon"

/* Type d'une trame defini dans le protocole PC2RON2011 */
typedef enum Frametype {
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
} Frametype;

/* Resultat d'un echange entre un client et le serveur */
typedef struct Result {
    int type;
    void* content;
} Result;


int check_frame(Frame frame);

/* Verification du format d'une trame */
const char* check_connect_format(Frame frame);
int check_initiate_format(Frame frame);
int check_order_format(Frame frame);


/* Verification des contraintes */
const char* check_connect_constraint(int sock, Players the_players);
int check_order_constraint(int sock, Players the_players);
int check_initiate_constraint(int sock, size_t nb_connected_players, Players the_players);

/* Verification du nom d'application et de la version du protocole */
int check_appname(char* appname);
int check_version(const char* version);

/* Reponses au client */
Result* respond(int sock, Players the_players);
Result* respond_initiate(int sock, Players the_players, Frame recv_frame);
Result* respond_connect(int sock, Players the_players, Frame recv_frame);
Result* respond_order(int sock, Players the_players, Frame recv_frame);

/* Envoi de trames au client (la plupart en broadcast) */
void send_broadcast(Players the_players, Frame frame);
void send_pause(Players the_players, const char* msg);
void send_start(Players the_players, const char* msg);
void send_user(Players the_players);
void send_turn(Players the_players, uint32_t elapsed_time);
void send_end(Players the_players);
void send_win(Players the_players, uint16_t uid);
void send_death(Players the_players, uint16_t uid);
void send_two_deaths(Players the_players, uint16_t uid1, uint16_t uid2);

#endif /* PROTOCOLE_H_ */
