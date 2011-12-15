/*
 * main.c
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */


#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sched.h>
#include <pthread.h>

#include "main.h"
#include "string.h"
#include "protocole.h"
#include "serveur.h"

#define NB_MAX_JOUEURS 2
#define NB_MAX_THREADS 10

extern int usleep (__useconds_t __useconds);

static int sock;
static pthread_mutex_t MUTEX_accept = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t MUTEX_inscripton = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t MUTEX_instant = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t COND_joueurs_inscrits = PTHREAD_COND_INITIALIZER;
static pthread_cond_t COND_instant = PTHREAD_COND_INITIALIZER;

static Players the_players;

/*@todo 
 * init_sequence(): Séquence d'initialisation
 * connect_player : connexion d'un joueur
 * register_player : inscription d'un joueur
 * send_countdown : compte à rebours
 * 
 * handle_winner() : s'il reste un seul joueur, il est alors le gagnant
 * handle_loosers() : verifier collision ou sortie de la grille
 * handle_order(Joueur j, Ordre o) : mise a jour des positions
 * end_game() : Envoyer le score aux joueurs puis fermer la connexion
*/


void handle_player_connection(int player_sock) {
    Result* result = NULL;
   
    do {
        result = respond(player_sock, the_players);
        if(result != NULL && result->type == NOT_CONNECTED) {
            pthread_exit(NULL);
        }
    } while (result == NULL || result->type != Initiate);
}

void handle_player_registration(int player_sock) {
    Result* result = NULL;
   
    do {
        result = respond(player_sock, the_players);
        
        if(result != NULL && result->type == NOT_CONNECTED) {
            /*pthread_exit(NULL);*/
        }
    } while (result == NULL || result->type != Connect);
}   

void send_countdown(int max_number) {
    char number[4];
    int i = 0;
    
    for(i = max_number; i >= 0; i--) {
        sprintf(number, "%d", i);
        send_pause(the_players, number);
        sleep(1);
    }
    
    send_start(the_players, "GO");
}

void handle_order(int player_sock) {
    Result* result = NULL;
    char* order = NULL;
    
    do {
        result = respond(player_sock, the_players);
        
        if(result != NULL && result->type == Order) {
            order = result->content;

            printf("\nordre recu : %s\n", order);

            if( 0 == strcmp(order, STRAIGHT_ORDER)) {
                printf("Tout Droit\n");
                
            } else if(0 == strcmp(order, LEFT_ORDER)) {
                printf("Gauche\n");
                
            } else if(0 == strcmp(order, RIGHT_ORDER)) {
                printf("Droite\n");
                
            } else if(0 == strcmp(order, ABORT_ORDER)) {
                printf("Abandon\n");
                
            } else {
                printf("Ordre inconnu");
            }
        }

        /* Attente de l'instant suivant */ 
        pthread_mutex_lock(&MUTEX_instant);
        pthread_cond_wait(&COND_instant, &MUTEX_instant);
        pthread_mutex_unlock(&MUTEX_instant);
        
    } while(result == NULL || result->type != NOT_CONNECTED);
}

void* THREAD_serveur(void *args) {
    SOCKET csock;
    
    /*   Déroulement d'une partie  */ 
    while (1) {
        /* Initialisation de la connexion socket avec le client */ 
        pthread_mutex_lock(&MUTEX_accept);
        csock = accept_client(sock);
        pthread_mutex_unlock(&MUTEX_accept);
        
        /* Attente de connexion et d'inscription du joueur */
        handle_player_connection(csock);
        handle_player_registration(csock);
        
        /* Attente de l'inscription de tous les joueurs  */ 
        pthread_mutex_lock(&MUTEX_inscripton);

        if(count_registered_players(the_players) == NB_MAX_JOUEURS) {
            printf("Info: Les joueurs sont tous inscrits !\n");
            pthread_cond_broadcast(&COND_joueurs_inscrits);
            
            /* Envoi de la trame User a tous les participants */
            send_user(the_players);
        
            /* Compte a rebours */
            send_countdown(5);
        } else {
            printf("Attente...");
            pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_inscripton);
        }
        pthread_mutex_unlock(&MUTEX_inscripton);

        /* Attente de l'ordre du joueur */ 
        handle_order(csock);
    }

    /* Fermeture de connexion */
    shutdown(csock, SHUT_RDWR);
}

void*  THREAD_instant(void *args) {
    int i = 1;
    while(1) {
        usleep(1000000);
        printf("\n---------------- instant %d ------------\n", i);
        pthread_mutex_lock(&MUTEX_instant);
        pthread_cond_broadcast(&COND_instant);
        i++;
        pthread_mutex_unlock(&MUTEX_instant);
    }
}


int main(void) {
    pthread_t threads[NB_MAX_THREADS];
    pthread_t thread_instant;

    void* status;
    long i;
    
    /* Initialisation des joueurs */
    the_players = create_the_players(NB_MAX_JOUEURS);
     
    /* Creation d'une socket  */ 
    sock = connect_server();

    /* Traceur d'instant */ 
    pthread_create(&thread_instant, NULL, THREAD_instant, NULL);

    /* Threads serveur */ 
    for(i=0; i < NB_MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
    }

    for(i=0;i<NB_MAX_THREADS;i++) {
        pthread_join(threads[i], &status);
    }

    close_connection(sock);

    return 0;
}
