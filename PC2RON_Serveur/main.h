/*
 * main.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef MAIN_H_
#define MAIN_H_

void handle_player_connection(int sock);
void handle_player_registration(int sock);
void handle_order(int sock);
void send_countdown(int max_number);

void* THREAD_serveur(void *args) __attribute__((noreturn));
void* THREAD_instant(void *args) __attribute__((noreturn));

#endif /* MAIN_H_ */
