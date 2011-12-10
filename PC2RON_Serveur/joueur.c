#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>



// Initialisation d'un joueur
void init_joueur(int sock, Joueur* j) {
    j->sock = sock;
    j->nom = NULL;
    j->dir = HAUT;
    j->id = 0;
    
    j->x = 0;
    j->y = 0;
    
    j->r = 0;
    j->v = 0;
    j->b = 0;
    
    j->estConnecte = 0;
    j->estInscrit = 0;
}

// Récupération des informations d'un client à partir de sa socket
Joueur* get_joueur(int sock, Joueur joueurs[]) {
    int i = 0;
    
    while (i < NB_MAX_JOUEURS && joueurs[i].sock != sock) {
        i++;
    }
    
    if(i == NB_MAX_JOUEURS) {
        return NULL;
    } else {
        return joueurs[i];
    }
}

// Inscrire ou désinscrire un joueur
int set_inscription_joueur(SOCKET sock, Joueur joueurs[], int booleen) {
    Joueur* j = get_joueur(sock, joueurs);
    j->estInscrit = booleen;
}

// Connecter ou déconnecter un joueur
int set_connexion_joueur(SOCKET sock, Joueur joueurs[], int booleen) {
    Joueur* j = get_joueur(sock, joueurs);
    j->estConnecte = booleen;
}