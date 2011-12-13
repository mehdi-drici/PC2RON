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

#include "protocole.h"
    
   /*  typedef enum {false, true} bool;  */ 

Trame creer_trame_ack(int ok);
Trame creer_trame_registered_ok(unsigned short id);
Trame creer_trame_registered_no(const char* message);
Trame creer_trame_user(Joueur j);
Trame creer_trame_win(unsigned short id);
Trame creer_trame_death(unsigned short id1);
Trame creer_trame_deaths(unsigned short id1, unsigned short id2);
Trame creer_trame_pause(const char* message);
Trame creer_trame_start(const char* message);
Trame creer_trame_turn(unsigned int t, Joueurs lesJoueurs);
Trame creer_trame_end(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUILDER_H */

