#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"
#include "erreur.h"

void init_joueurs(Joueurs lesJoueurs, size_t taille) {
    size_t i = 0;
    lesJoueurs = malloc(sizeof(struct Joueurs));
    lesJoueurs->nbJoueurs = taille;
    lesJoueurs->joueur = calloc(taille, sizeof(struct Joueur));
    
    for(i=0; i < lesJoueurs->nbJoueurs; i++) {
        lesJoueurs->joueur[i] = creer_joueur();
    }
}

Joueur creer_joueur() {
    Joueur j = malloc(sizeof(struct Joueur));
    
    j->sock = -1;
    
    j->nom = NULL;
    j->dir = HAUT;
    j->id = 0;
    
       /*  @todo créer struct Point  */ 
    j->positions[0].x = 0;
    j->positions[0].y = 0;
    
       /*  @todo créer struct RVB  */
    j->couleur.r = 0;
    j->couleur.v = 0;
    j->couleur.b = 0;
    
    j->speed = LENT;
    
    j->estConnecte = 0;
    j->estInscrit = 0;
    
    return j;
}

   /*   Récupération des informations d'un client à partir de sa socket  */ 
Joueur get_joueur_par_sock(int sock, const Joueurs lesJoueurs) {
    size_t i = 0;
    
    while (i < lesJoueurs->nbJoueurs) {
        if(lesJoueurs->joueur[i]->sock == sock) {
            return lesJoueurs->joueur[i];
        }
        
        i++;
    }
    
    return NULL;
}

   /*   Récupération des informations d'un client à partir de son id  */ 
Joueur get_joueur_par_id(unsigned short id, Joueurs lesJoueurs) {
    size_t i = 0;
    
    while (i < lesJoueurs->nbJoueurs) {
        if(lesJoueurs->joueur[i]->id == id) {
            return lesJoueurs->joueur[i];
        }
        
        i++;
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

/*
int get_max_joueurs(const Joueurs lesJoueurs) {
    int nbMaxJoueurs = sizeof(lesJoueurs) / sizeof(Joueur);
    
    Joueur tab[5];
    printf("sizeof(tab) = %d\n", sizeof(tab));
    printf("sizeof(lesJoueurs) = %d\n", sizeof(lesJoueurs));
    printf("sizeof(Joueur) = %d\n", sizeof(Joueur));
    printf("sizeof(*lesJoueurs) = %d\n", sizeof(*lesJoueurs));
    printf("sizeof(struct Joueur) = %d\n", sizeof(struct Joueur));
    
    return nbMaxJoueurs;
}
*/ 