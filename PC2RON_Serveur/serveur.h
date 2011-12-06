/*
 * serveur.h
 *
 *  Created on: 30 nov. 2011
 *      Author: mehdi
 */

#ifndef SERVEUR_H_
#define SERVEUR_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define PORT 5555
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
//typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

int etablir_connexion();
int accepter_client(int sock);
void fermer_connexion(int sock);

#endif /* SERVEUR_H_ */
