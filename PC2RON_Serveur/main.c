/*
 * main.c
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#include "main.h"

SOCKET sock;
pthread_mutex_t MUTEX_compteur;

void* THREAD_serveur(void *args) {
	SOCKET csock;
        //int* p_idClient = (int*) args;
        //int idClient = *p_idClient;
        int continuer = 1;
        int erreur = 0;
        Joueur j1 = {10, "Mehdi Drici", 50, 50, 50, 19, 21, HAUT};
        Joueur j2 = {11, "Will Smith", 50, 50, 50, 19, 21, BAS};
        Joueur j[2] = {j1, j2};
        
	pthread_mutex_lock(&MUTEX_compteur);
	csock = accepter_client(sock);
        pthread_mutex_unlock(&MUTEX_compteur);
        
        /*
	while (continuer) {
		erreur = recevoir_trame(csock, &trameRecue);
                                
                if(erreur == ERR_RCPT_FANION_TRAME) {
                    break;
                }
                
                if(erreur == ERR_RCPT_TRAME) {
                    break;
                }
                
                afficher_trame(trameRecue);
                
                // Fin de transmission
                if(trameRecue.fanion == TRAME_SPECIALE) {
                    continuer = 0;
                }
	}
        */
        get_resultat(csock);
        envoyer_start(csock, "Bonjour Monsieur Drici !");
        envoyer_pause(csock, "Ceci est une pause!");
        envoyer_users(csock, j);
        
	/* Fermeture de connexion */
	shutdown(csock, SHUT_RDWR);

    return NULL;
}

int main(void) {
	pthread_t threads[NB_THREAD];
	void* status;
	long i;

	// Création d'une socket
	sock = etablir_connexion();

	pthread_mutex_init(&MUTEX_compteur,NULL);
        for(i=0; i < NB_THREAD; i++) {
            pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
        }

	for(i=0;i<NB_THREAD;i++) {
            pthread_join(threads[i], &status);
	}

	fermer_connexion(sock);

    return 0;
}
