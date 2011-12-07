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
        
	pthread_mutex_lock(&MUTEX_compteur);
	csock = accepter_client(sock);
        //debug
        printf("----------------------\n\n");
        printf("Un client se connecte !\n");
        printf("----------------------\n");
	//debug
        pthread_mutex_unlock(&MUTEX_compteur);
        
        Trame trameRecue;
        int continuer = 1;
        int erreur = 0;
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
        
        // Envoi de trame
        Donnee d = creer_chaine("toto");
        Donnee d2 = creer_entierSigne1(200);
        Donnee d3 = creer_entierSigne2(33000);
        Donnee d4 = creer_entierNonSigne1(-10);
        Donnee d5 = creer_entierNonSigne2(65639);
        Donnee d6 = creer_entierNonSigne4(-20);
        
        afficher_donnee(d);
        
        printf("\nTaille (c) = %d\n", d.chaine.taille);
        
        //Donnee d2 = creer_entierNonSigne2(-19);
        //Donnee d3 = creer_entierNonSigne2(70000);
        
        Trame t = creer_trame(10);
        ajouter_donnee(&t, d);
        ajouter_donnee(&t, d2);
        ajouter_donnee(&t, d3);
        ajouter_donnee(&t, d4);
        ajouter_donnee(&t, d5);
        ajouter_donnee(&t, d6);
        afficher_trame(t);
        
        //debug
        //printf("t.fanion = %d\n", t.fanion);

        //printf("t.id = %d\n", t.id);
        //printf("t.nbDonnees = %d\n", t.nbDonnees);
        //debug


        //envoyer_donnee(csock, d);
        //envoyer_donnee(csock, d);
        //envoyer_donnee(csock, d2);
        //envoyer_donnee(csock, d2);
        
        envoyer_trame(csock, t);
        
        // Resultat attendu: { 0x0A, string "toto" }
        //afficher_donnee(d);
        //afficher_donnee(d2);
        //afficher_trame(t);
        
        //afficher_trame(t);
        printf("----------------------\n\n");
        printf("Deconnexion du client\n");
        printf("----------------------\n");
        
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
