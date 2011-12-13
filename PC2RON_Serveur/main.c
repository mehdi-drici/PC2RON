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

#define NB_MAX_JOUEURS 4
#define NB_MAX_THREADS 10

extern int usleep (__useconds_t __useconds);

static int sock;
static pthread_mutex_t MUTEX_accept = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t MUTEX_inscripton = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t MUTEX_instant = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t COND_joueurs_inscrits = PTHREAD_COND_INITIALIZER;
static pthread_cond_t COND_instant = PTHREAD_COND_INITIALIZER;

static int nbJoueursCo = 0;
static int nbJoueurs = 0;

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


/*Joueur lesJoueurs[NB_MAX_JOUEURS];*/
Joueurs lesJoueurs;
Joueur j;

void* THREAD_serveur(void *args) {
    SOCKET csock;
    int joueurInscrit = 0;
    int estConnecte = 0;
    Resultat* res;
    
    /*   Déroulement d'une partie  */ 
    while (1) {
        /*   init de la socket  */ 
        pthread_mutex_lock(&MUTEX_accept);
        csock = accepter_client(sock);
        nbJoueurs++;
        pthread_mutex_unlock(&MUTEX_accept);
        
        /* Connexion du joueur */
        do {
            usleep(750);
            
            res = get_resultat_echange(csock, lesJoueurs);
            
            if(res != NULL && res->typeTrame == Initiate) {
                printf("Le joueur est connecte !!!!!!!!!!!!!!!!!!!!\n");
                estConnecte = 1;
            }
            
            /* Le joueur s'est deconnecte */
            if(res != NULL && res->typeTrame == NOT_CONNECTED) {
                printf("Le joueur n'est plus connecte\n");
                pthread_exit(NULL);
            }
            
        } while (!estConnecte);
        
        /*   Inscription du joueur */ 
        do {
            usleep(1000);
            res = get_resultat_echange(csock, lesJoueurs);
            
            if(res != NULL && res->typeTrame == Connect) {
                joueurInscrit = 1;
                j = (Joueur) (res->contenu);
                printf("Id de la socket %d : %d\n", csock, j->id);
                nbJoueursCo++;
            }
            
            /* Le joueur s'est deconnecte */
            if(res != NULL && res->typeTrame == NOT_CONNECTED) {
                printf("Le joueur n'est plus connecte\n");
                pthread_exit(NULL);
            }
        } while (!joueurInscrit);
        
        /* Attente de l'inscription de tous les joueurs  */ 
        pthread_mutex_lock(&MUTEX_inscripton);

        if(nbJoueursCo == NB_MAX_JOUEURS) {
            printf("Info: Les joueurs sont tous inscrits !\n");
            pthread_cond_broadcast(&COND_joueurs_inscrits);

        } else {
            printf("Attente...");
            pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_inscripton);
        }
        pthread_mutex_unlock(&MUTEX_inscripton);

           /*   Envoi de la trame User  */ 
           /*  envoyer_users(csock, j);  */ 

           /*   Décompte  */ 
        /*@todo verifier que le joueur est bien connecte */
        envoyer_pause(csock, "3", lesJoueurs);
        sleep(1);

        envoyer_pause(csock, "2", lesJoueurs);
        sleep(1);

        envoyer_pause(csock, "1", lesJoueurs);
        sleep(1);

        envoyer_start(csock, "GO!", lesJoueurs);

           /*   Attente de l'ordre du joueur  */ 
        do {
            res = get_resultat_echange(csock, lesJoueurs);
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

               /*   Attente de l'instant suivant  */ 
            pthread_mutex_lock(&MUTEX_instant);
            pthread_cond_wait(&COND_instant, &MUTEX_instant);
            pthread_mutex_unlock(&MUTEX_instant);
        } while(res != NULL && res->typeTrame != NOT_CONNECTED);

        /* Fermeture de connexion */
        shutdown(csock, SHUT_RDWR);
    }    /*  Fin Partie  */ 
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
    size_t compteur;
    
       /*   Initialisation des joueurs  */
     
     lesJoueurs = malloc(sizeof(struct Joueurs));
     lesJoueurs->nbJoueurs = NB_MAX_JOUEURS;
     lesJoueurs->joueur = malloc(NB_MAX_JOUEURS * sizeof(struct Joueur));
     
     for(compteur=0; compteur < lesJoueurs->nbJoueurs; compteur++) {
        lesJoueurs->joueur[compteur] = creer_joueur();
      }
     
     /*init_joueurs(lesJoueurs, NB_MAX_JOUEURS);*/
     
      /*init_protocole(lesJoueurs);*/
    
       /*   Création d'une socket  */ 
    sock = etablir_connexion();

       /*   Traceur d'instant  */ 
    pthread_create(&thread_instant, NULL, THREAD_instant, NULL);

       /*   Threads serveur  */ 
    for(i=0; i < NB_MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
    }

    for(i=0;i<NB_MAX_THREADS;i++) {
        pthread_join(threads[i], &status);
    }

    fermer_connexion(sock);

    return 0;
}
