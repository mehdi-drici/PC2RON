/*
 * main.c
 *
 *  Created on: 27 nov. 2011
 *      Author: mehdi
 */

#include "main.h"
#include "string.h"

#define NB_MAX_JOUEURS 3

SOCKET sock;
pthread_mutex_t MUTEX_accept = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MUTEX_inscripton = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MUTEX_instant = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t COND_joueurs_inscrits = PTHREAD_COND_INITIALIZER;
pthread_cond_t COND_instant = PTHREAD_COND_INITIALIZER;

int nbJoueursCo = 0;
int nbJoueurs = 0;

Joueurs lesJoueurs;
Joueur j;

void* THREAD_serveur(void *args) {
    SOCKET csock;
    int joueurInscrit = 0, estConnecte = 0;
    Resultat* res;
    
       /*   Déroulement d'une partie  */ 
    while (1) {
           /*   init de la socket  */ 
        pthread_mutex_lock(&MUTEX_accept);
        csock = accepter_client(sock);
        /*init_joueur(csock, lesJoueurs->joueur[nbJoueurs]);*/
        nbJoueurs++;
        pthread_mutex_unlock(&MUTEX_accept);
        
        /* Connexion du joueur */
        do {
            sleep(2);
            res = get_resultat_echange(csock, lesJoueurs);
            
            if(res != NULL && res->typeTrame == Initiate) {
                estConnecte = 1;
            }
        } while (!estConnecte);
        
        /*   Inscription du joueur */ 
        do {
            sleep(2);
            res = get_resultat_echange(csock, lesJoueurs);
            
            if(res != NULL && res->typeTrame == Connect) {
                joueurInscrit = 1;
                j = (Joueur) (res->contenu);
                printf("Id de la socket %d : %d\n", csock, j->id);
                nbJoueursCo++;
            }
        } while (!joueurInscrit);

           /*   Attente de l'inscription de tous les joueurs  */ 
        pthread_mutex_lock(&MUTEX_inscripton);

        if(nbJoueursCo == NB_MAX_JOUEURS) {
            printf("Info: Les joueurs sont tous inscrits !\n");
            pthread_cond_broadcast(&COND_joueurs_inscrits);

        } else {
            pthread_cond_wait(&COND_joueurs_inscrits, &MUTEX_inscripton);
        }
        pthread_mutex_unlock(&MUTEX_inscripton);

           /*   Envoi de la trame User  */ 
           /*  envoyer_users(csock, j);  */ 

           /*   Décompte  */ 
        envoyer_pause(csock, "3", lesJoueurs);
        sleep(1);

        envoyer_pause(csock, "2", lesJoueurs);
        sleep(1);

        envoyer_pause(csock, "1", lesJoueurs);
        sleep(1);

        envoyer_start(csock, "GO!", lesJoueurs);

           /*   Attente de l'ordre du joueur  */ 
        while(1) {
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
        }

        /* Fermeture de connexion */
        shutdown(csock, SHUT_RDWR);
    }    /*  Fin Partie  */ 
}

void*  THREAD_instant(void *args) {
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
    pthread_t threads[NB_MAX_JOUEURS];
    pthread_t thread_instant;

    void* status;
    long i;
    
       /*  fprintf(stderr, "toto erreur");  */ 
    fprintf(stderr, "Dans la fonction %s...\n", __func__);
    
       /*   Initialisation du protocole  */
    lesJoueurs = malloc(sizeof(struct Joueurs));
    lesJoueurs->nbMaxJoueurs = NB_MAX_JOUEURS;
    lesJoueurs->joueur = malloc(NB_MAX_JOUEURS * sizeof(struct Joueur));
    /*init_protocole(lesJoueurs);*/
    
       /*   Création d'une socket  */ 
    sock = etablir_connexion();

       /*   Traceur d'instant  */ 
    pthread_create(&thread_instant, NULL, THREAD_instant, NULL);

       /*   Threads serveur  */ 
    for(i=0; i < NB_MAX_JOUEURS; i++) {
        pthread_create(&threads[i], NULL, THREAD_serveur, (long*) i);
    }

    for(i=0;i<NB_MAX_JOUEURS;i++) {
        pthread_join(threads[i], &status);
    }

    fermer_connexion(sock);

    return 0;
}
