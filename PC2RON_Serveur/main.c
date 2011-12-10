/*
 * main.c
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#include "main.h"

#define NB_MAX_JOUEURS 3

SOCKET sock;
pthread_mutex_t MUTEX_accept = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MUTEX_inscripton = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MUTEX_instant = PTHREAD_MUTEX_INITIALIZER;

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
    erreur = pthread_mutex_lock(&MUTEX_accept);
    csock = accepter_client(sock);
    erreur = pthread_mutex_unlock(&MUTEX_accept);
    
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
    erreur = pthread_mutex_lock(&MUTEX_inscripton);
    printf("erreur = %d\n", erreur);
    sched_yield();
    //pthread_mutex_unlock(&MUTEX_compteur);
    //printf("salut");
    sched_yield();
    
    if(nbJoueursCo == NB_MAX_JOUEURS) {
        printf("Info: Les joueurs sont tous inscrits !\n");
        pthread_cond_broadcast(&COND_joueurs_inscrits);
        
    } else {
        printf("attente ! \n");
        pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_inscripton);
    }
    
    printf("erreur = %d\n", erreur);
    erreur = pthread_mutex_unlock(&MUTEX_inscripton);

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
            
            printf("\nordre recu : %s\n", ordre);
            
            if(strcmp(ordre, ORDRE_DROIT) == 0) {
                printf("Tout Droit\n");
            } else if(strcmp(ordre, ORDRE_GAUCHE) == 0) {
                printf("Gauche\n");
            } else if(strcmp(ordre, ORDRE_DROITE) == 0) {
                printf("Droite\n");
            } else if(strcmp(ordre, ORDRE_ABANDON) == 0) {
                printf("Abandon\n");
            } else {
                printf("Ordre inconnu");
            }
        }
        
        pthread_mutex_lock(&MUTEX_instant);
        pthread_cond_wait(&COND_instant, &MUTEX_instant);
        pthread_mutex_unlock(&MUTEX_instant);
    }
    
    /* Fermeture de connexion */
    shutdown(csock, SHUT_RDWR);
}

void* THREAD_instant(void *args) {
    int i = 1;
    while(1) {
        sleep(2);
        printf("---------------- instant %d ------------\n", i);
        sched_yield();
        pthread_mutex_lock(&MUTEX_instant);
        sched_yield();
        pthread_cond_broadcast(&COND_instant);
        sched_yield();
        i++;
        pthread_mutex_unlock(&MUTEX_instant);
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
        
        pthread_create(&thread_instant, NULL, THREAD_instant, NULL);
        for(i=0; i < NB_THREAD; i++) {
            pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
        }
        
	for(i=0;i<NB_THREAD;i++) {
            pthread_join(threads[i], &status);
	}

	fermer_connexion(sock);

    return 0;
}
