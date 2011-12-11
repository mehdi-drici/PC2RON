#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>

// Initialisation d'un joueur
void init_joueur(int sock, Joueur* j) {
    j->sock = sock;
    j->nom = NULL;
    j->dir = HAUT;
    j->id = 0;
    
    //@todo créer struct Point
    j->x = 0;
    j->y = 0;
    
    //@todo créer struct RVB
    j->r = 0;
    j->v = 0;
    j->b = 0;
    
    j->estConnecte = 0;
    j->estInscrit = 0;
}

// Récupération des informations d'un client à partir de sa socket
Joueur* get_joueur_par_sock(int sock, Joueurs lesJoueurs) {
    int i = 0;
    
    while (i < lesJoueurs.nbJoueurs && lesJoueurs.joueur[i].sock != sock) {
        i++;
    }
    
    if(i == lesJoueurs.nbJoueurs) {
        return NULL;
    } else {
        return lesJoueurs.joueur + i;
    }
}

// Récupération des informations d'un client à partir de son id
Joueur* get_joueur_par_id(int id, Joueurs lesJoueurs) {
    int i = 0;
    
    while (i < lesJoueurs.nbJoueurs && lesJoueurs.joueur[i].id != id) {
        i++;
    }
    
    if(i == lesJoueurs.nbJoueurs) {
        return NULL;
    } else {
        return lesJoueurs.joueur + i;
    }
}

// Inscrire ou désinscrire un joueur
int set_inscription_joueur(Joueur* j, int booleen) {
    j->estInscrit = booleen;
}

// Connecter ou déconnecter un joueur
int set_connexion_joueur(Joueur* j, int booleen) {
    j->estConnecte = booleen;
}

int est_inscrit(const Joueur j) {
    return j.estInscrit;
}

int est_connecte(const Joueur j) {
    return j.estConnecte;
}