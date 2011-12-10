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
int nbJoueurs = 0;

Joueur j[3];

void* THREAD_serveur(void *args) {
    SOCKET csock;
    Joueur* j;
    int joueurInscrit = 0;
    Resultat* res;
    int i;
    
    // init de la socket
    pthread_mutex_lock(&MUTEX_accept);
    csock = accepter_client(sock);
    
    // Initialisation du protocole
    init_protocole(j, 3);
    init_joueur(csock, &j[nbJoueurs]);
    
    pthread_mutex_unlock(&MUTEX_accept);
    
    // Inscription du client   
    do {
        sleep(5);
        
        res = get_resultat_echange(csock);
        
        if(res != NULL && res->typeTrame == Connect) {
            joueurInscrit = 1;
            j = (Joueur*) (res->contenu);
            printf("Id de la socket %d : %d\n", csock, j->id);
            nbJoueursCo++;
        }
    } while (!joueurInscrit);
    
    // Attente de l'inscription de tous les joueurs
    pthread_mutex_lock(&MUTEX_inscripton);
    
    if(nbJoueursCo == NB_MAX_JOUEURS) {
        printf("Info: Les joueurs sont tous inscrits !\n");
        pthread_cond_broadcast(&COND_joueurs_inscrits);
        
    } else {
        pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_inscripton);
    }

    pthread_mutex_unlock(&MUTEX_inscripton);

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
    
    // Attente de l'ordre du joueur
    while(1) {
        res = get_resultat_echange(csock);
        if(res->typeTrame == Order) {
            char* ordre = res->contenu;
            
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
        
        // Attente de l'instant suivant
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
        pthread_mutex_lock(&MUTEX_instant);
        pthread_cond_broadcast(&COND_instant);
        i++;
        pthread_mutex_unlock(&MUTEX_instant);
    }
}

int main(void) {
    pthread_t threads[NB_THREAD];
    pthread_t thread_instant;

    void* status;
    long i;
    
    //fprintf(stderr, "toto erreur");
    
    // Création d'une socket
    sock = etablir_connexion();

    // Traceur d'instant
    pthread_create(&thread_instant, NULL, THREAD_instant, NULL);

    // Threads serveur
    for(i=0; i < NB_THREAD; i++) {
        pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
    }

    for(i=0;i<NB_THREAD;i++) {
        pthread_join(threads[i], &status);
    }

    fermer_connexion(sock);

    return 0;
}
