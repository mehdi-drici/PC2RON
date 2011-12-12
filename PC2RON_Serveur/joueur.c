#include "joueur.h"
#include "erreur.h"
#include <stdio.h>
#include <stdlib.h>

int ajouter_joueur(Joueurs lesJoueurs, Joueur j) {
    int nbJoueurs = lesJoueurs->nbJoueurs;
    
    if(lesJoueurs->nbJoueurs < lesJoueurs->nbMaxJoueurs) {
        lesJoueurs->nbJoueurs++;
        lesJoueurs->joueur[nbJoueurs] = j;
        return SUCCESS;
    }
    
    PRINT_LIMIT_PLAYERS_CONNECTED_REACHED();
    return ERROR;
}

Joueur creer_joueur(int sock) {
    Joueur j = malloc(sizeof(struct Joueur));
    j->sock = sock;
    
    j->nom = NULL;
    j->dir = HAUT;
    j->id = 0;
    
       /*  @todo créer struct Point  */ 
    j->x = 0;
    j->y = 0;
    
       /*  @todo créer struct RVB  */ 
    j->r = 0;
    j->v = 0;
    j->b = 0;
    
    j->estConnecte = 0;
    j->estInscrit = 0;
    
    return j;
}

   /*   Récupération des informations d'un client à partir de sa socket  */ 
Joueur get_joueur_par_sock(int sock, Joueurs lesJoueurs) {
    int i = 0;
    printf("nbJoueurs = %d\n", lesJoueurs->nbJoueurs);
    while (i < lesJoueurs->nbJoueurs) {
        if(lesJoueurs->joueur[i]->sock == sock) {
            return lesJoueurs->joueur[i];
        }
    }
    
    return NULL;
}

   /*   Récupération des informations d'un client à partir de son id  */ 
Joueur get_joueur_par_id(unsigned short id, Joueurs lesJoueurs) {
    int i = 0;
    
    while (i < lesJoueurs->nbJoueurs) {
        if(lesJoueurs->joueur[i]->id == id) {
            return lesJoueurs->joueur[i];
        }
    }
    
    return NULL;
}

   /*   Inscrire ou désinscrire un joueur  */ 
void set_inscription_joueur(Joueur j, int booleen) {
    j->estInscrit = booleen;
}

   /*   Connecter ou déconnecter un joueur  */ 
void set_connexion_joueur(Joueur j, int booleen) {
    j->estConnecte = booleen;
}

int est_inscrit(const Joueur j) {
    return j->estInscrit;
}

int est_connecte(const Joueur j) {
    return j->estConnecte;
}