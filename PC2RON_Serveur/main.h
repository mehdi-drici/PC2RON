/*
 * main.h
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sched.h>
#include <pthread.h>

#include "protocole.h"
#include "serveur.h"

#define NB_THREAD 3

void* THREAD_serveur(void *args) __attribute__((noreturn));
void* THREAD_instant(void *args) __attribute__((noreturn));

#endif /* MAIN_H_ */
