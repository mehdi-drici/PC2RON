/*
 * main.c
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#include "main.h"

#define NB_MAX_JOUEURS 3

SOCKET sock;
pthread_mutex_t MUTEX_compteur = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND_joueurs_inscrits = PTHREAD_COND_INITIALIZER;
pthread_cond_t COND_instant = PTHREAD_COND_INITIALIZER;
int nbJoueursCo = 0;
Joueur j[3];

void* THREAD_serveur(void *args) {
    SOCKET csock;
    
    int joueurInscrit = 0;
    int erreur;
    Resultat res;
    int i;
    
    // init de la socket
    //pthread_mutex_lock(&MUTEX_compteur);
    printf("toto tata sd sk\n");
    csock = accepter_client(sock);
    //pthread_mutex_unlock(&MUTEX_compteur);
        
    // Inscription du client   
    do {
        res = get_resultat(csock);
        
        if(res.typeTrame == Connect) {
            joueurInscrit = 1;
            nbJoueursCo++;
        }
    } while (!joueurInscrit);
    
    printf("&&inscrit !\n");
    printf("&&nbJoueursCo = %d\n", nbJoueursCo);
    
    // Attente de l'inscription de tous les joueurs
    pthread_mutex_lock(&MUTEX_compteur);
    sched_yield();
    //pthread_mutex_unlock(&MUTEX_compteur);
    //printf("salut");
    sched_yield();
    
    if(nbJoueursCo == NB_MAX_JOUEURS) {
        printf("Info: Les joueurs sont tous inscrits !\n");
        pthread_cond_broadcast(&COND_joueurs_inscrits);
        
    } else {
        printf("attente ! \n");
        pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_compteur);
    }
    
    pthread_mutex_unlock(&MUTEX_compteur);

    // Envoi de la trame User
    //envoyer_users(csock, j);
    
    // Décompte
    envoyer_pause(csock, "3");
    sleep(1);
    
    envoyer_pause(csock, "2");
    sleep(1);
    
    envoyer_pause(csock, "1");
    sleep(1);
    
    envoyer_start(csock, "GO!");
    
    while(1) {
        res = get_resultat(csock);
        if(res.typeTrame == Order) {
            char* ordre = res.contenu;
            
            if(ordre == ORDRE_DROIT) {
                printf("Tout Droit\n");
            } else if(ordre == ORDRE_GAUCHE) {
                printf("Gauche\n");
            } else if(ordre == ORDRE_DROITE) {
                printf("Droite\n");
            } else if(ordre == ORDRE_ABANDON) {
                printf("Abandon\n");
            } else {
                printf("Ordre inconnu");
            }
        }
        
        pthread_mutex_lock(&MUTEX_compteur);
        sched_yield();
        pthread_cond_wait(&COND_instant, &MUTEX_compteur);
        sched_yield();
        pthread_mutex_unlock(&MUTEX_compteur);
    }
    
    /* Fermeture de connexion */
    shutdown(csock, SHUT_RDWR);
}

void* THREAD_instant(void *args) {
    while(1) {
        sleep(2);
        sched_yield();
        pthread_mutex_lock(&MUTEX_compteur);
        sched_yield();
        pthread_cond_signal(&COND_instant);
        sched_yield();
        pthread_mutex_unlock(&MUTEX_compteur);
    }
}

int main(void) {
	pthread_t threads[NB_THREAD];
        pthread_t thread_instant;
        
	void* status;
	long i;

	// Création d'une socket
	sock = etablir_connexion();
        
        // Initialisation du mutex
	//pthread_mutex_init(&MUTEX_compteur,NULL);
        
        // Initialisation des conditions
        //pthread_cond_init(&COND_instant, NULL);
        //pthread_cond_init(&COND_joueurs_inscrits, NULL);
        
        //pthread_create(&thread_instant, NULL, THREAD_instant, NULL);
        for(i=0; i < NB_THREAD; i++) {
            pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
        }
        
	for(i=0;i<NB_THREAD;i++) {
            pthread_join(threads[i], &status);
	}

	fermer_connexion(sock);

    return 0;
}
