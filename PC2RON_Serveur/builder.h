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
    
Frame create_ack(int boolean);
Frame create_registered_ok(uint16_t uid);
Frame create_registered_no(const char* msg);
Frame create_user(Player player);
Frame create_win(uint16_t id);
Frame create_death(uint16_t uid);
Frame create_two_deaths(uint16_t uid1, uint16_t uid2);
Frame create_pause(const char* msg);
Frame create_start(const char* msg);
Frame create_turn(uint32_t time, Players the_players);
Frame create_end(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* BUILDER_H */

