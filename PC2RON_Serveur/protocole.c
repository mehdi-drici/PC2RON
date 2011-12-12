#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "erreur.h"
#include "protocole.h"
#include "builder.h"
#include "reception.h"
#include "envoi.h"
#include "joueur.h"

   /*   Nombre courant de joueurs inscrits  */ 
unsigned short nbJoueursInscrits = 0;
int nbMaxJoueurs = 0;

   /*   Requetes du client  */ 
char* get_order(SOCKET sock, Trame t, Joueurs lesJoueurs) {
    unsigned char* o = NULL;
    
    Joueur j = get_joueur_par_sock(sock, lesJoueurs);
    
       /*   Un joueur ne peut envoyer d'ordre que s'il est inscrit  */ 
    if (j != NULL && !(j->estInscrit)) {
        fprintf(stderr, "Le joueur avec la socket %d n'est pas inscrit !\n", sock);
    }
    
       /*   Verification de la trame Init recue  */ 
    else if(t->nbDonnees == 1 &&
       t->donnees[0]->type == CHAINE) {
        o = t->donnees[0]->chaine.texte;
    } 
    
    return o;
}

   /*   Point d'entree du protocole   */ 
   /*   Si resultat NULL Alors il y'a eu une erreur lors de l'échange  */ 
   /*   qui sera redirigée vers le flux d'erreurs  */ 
Resultat* get_resultat_echange(SOCKET sock, Joueurs lesJoueurs) {
    Joueur j;
    char* o;
    Resultat* res = (Resultat*) malloc(sizeof(Resultat));
    Trame trameRecue = recevoir_trame(sock);
       /*  recevoir_trame(sock, &trameRecue);  */ 
    
       /*   Deconnexion brutale du joueur  */ 
    if(trameRecue == NULL) {
        set_connexion_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        set_inscription_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        free(res);
        return NULL;
    } 
    
       /*  debug  */ 
    printf("#Client : ");
    afficher_trame(trameRecue);
       /*  debug  */ 
    
       /*  @todo modifier Deconnexion du joueur  */ 
    if(trameRecue->fanion == TRAME_SPECIALE) {
        set_connexion_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        set_inscription_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        free(res);
        
        return NULL;
    }
    
    switch(trameRecue->id) {      
        case Connect:
            j = repondre_connect(sock, trameRecue, lesJoueurs);
            
            if(j != NULL) {
                res = malloc(sizeof(Resultat));
                res->typeTrame = Connect;
                res->contenu = j;    
            } else {
                PRINT_CONNECT_ERROR(sock);
            }
            break;
        
        case Initiate:
            repondre_initiate(sock, trameRecue, lesJoueurs);
            res = malloc(sizeof(Resultat));
            res->contenu = NULL;
            res->typeTrame = Initiate;
            break;
        
        case Order:
            o = get_order(sock, trameRecue, lesJoueurs);
            res = malloc(sizeof(Resultat));
            res->typeTrame = Order;
            if(o != NULL) {
                res->contenu = o;
            } else {
                PRINT_ORDER_ERROR(sock);
            }
            break;
        
        default:
            PRINT_UNKNOWN_FRAME_TYPE(trameRecue->id);
            break;
    }
    
    return res;
}

   /*   Reponses au client  */ 
int repondre_initiate(SOCKET sock, Trame t, Joueurs lesJoueurs) {
    Joueur j = get_joueur_par_sock(sock, lesJoueurs);
    
    /*  char* sAppName, sAppVersion;  */ 
    int error = ERROR;
    
    /*   init de la trame à renvoyer par un ack negatif  */ 
    Trame trameAck = creer_trame_ack(0);
    
       /*  @todo un joueur ne peut pas se connecter plus d'une fois  */ 
    if (j != NULL && j->estConnecte) {
        PRINT_ALREADY_CONNECTED(j);
    }
    
       /*   Verification de la trame Init recue  */ 
    else if(t->nbDonnees != 2) {
        PRINT_WRONG_DATA_SIZE(sock, S_INITIATE);
    } 
    
    else if(t->donnees[0]->type != CHAINE ||
       t->donnees[1]->type != CHAINE) {
        PRINT_WRONG_FORMAT(S_INITIATE);
    } 
    
    else {
           /*   Reponse a la requete Init  */ 
        char* sAppName = t->donnees[0]->chaine.texte;
           /*   On enlève le '?'  */ 
        sAppName[strlen(sAppName) - 1] = '\0';
        
        char* sAppVersion = t->donnees[1]->chaine.texte;
        
        if(strcmp(sAppName, NOM_APPLICATION) != 0) {
            PRINT_WRONG_APPNAME(sAppName);
            
        } else if(strcmp(sAppVersion, NOM_VERSION_PROTOCOLE) != 0) {
            PRINT_UNSUPPORTED_VERSION(sAppVersion);
            
        } else {            
            /* Connexion du nouveau joueur  */ 
            if(ajouter_joueur(lesJoueurs, creer_joueur(sock)) == SUCCESS) {
                error = SUCCESS;
                set_connexion_joueur(get_joueur_par_sock(sock, lesJoueurs), 1);
                free_trame(trameAck);
                trameAck = creer_trame_ack(1);
            }
        }
    }
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameAck);
       /*  debug  */ 
    
    envoyer_trame(sock, trameAck);
    
    return error;
}

Joueur repondre_connect(SOCKET sock, Trame t, Joueurs lesJoueurs) {   
    Trame trameReg;
    Joueur j = NULL;
    Joueur j2 = NULL;
    
    unsigned char r, v, b;
    char* nom;
    
       /*  @todo Un joueur doit etre connecte pour s'inscrire  */ 
    j2 = get_joueur_par_sock(sock, lesJoueurs);
    
    if (j2 != NULL && !(j2->estConnecte)) {
        trameReg = creer_trame_registered_no(NOT_CONNECTED);
        fprintf(stderr, "Le joueur avec la socket %d doit etre connecte pour s'inscrire\n", sock);
    }
    
       /*  @todo Un joueur ne peut pas s'inscrire plus d'une fois  */ 
    else if (j2 != NULL && j2->estInscrit) {
        trameReg = creer_trame_registered_no(ALREADY_CONNECTED);
        fprintf(stderr, "Le joueur avec la socket %d est deja connecte\n", sock);
    }
    
       /*   @todo Verification du quota de joueurs  */ 
    else if(nbJoueursInscrits == lesJoueurs->nbMaxJoueurs) {
        trameReg = creer_trame_registered_no(LIMIT_PLAYERS_REGISTERED_REACHED);
         fprintf(stderr, "Le nombre max de joueurs inscrit a été atteint\n");
    }
    
       /*   Verification de la trame Init recue  */ 
    else if(t->nbDonnees != 4) {
        trameReg = creer_trame_registered_no(WRONG_FRAME_FORMAT);
           /*  fprintf(stderr, MSG_ERR_TRAME);  */ 
        
    } else if(t->donnees[0]->type != ENTIER_NON_SIGNE1 ||
            t->donnees[1]->type != ENTIER_NON_SIGNE1 ||
            t->donnees[2]->type != ENTIER_NON_SIGNE1) {
        trameReg = creer_trame_registered_no(WRONG_RGB_FORMAT);
           /*  fprintf(stderr, MSG_ERR_RVB);  */ 
        
    }  else if(t->donnees[3]->type != CHAINE) {
        trameReg = creer_trame_registered_no(WRONG_NAME_FORMAT);
           /*  fprintf(stderr, MSG_ERR_NOM);  */ 
        
    } else {
           /*  j = malloc(sizeof(Joueur));  */ 
        j = get_joueur_par_sock(sock, lesJoueurs);
        
           /*   Reponse a la requete Connect  */ 
        r = t->donnees[0]->entierNonSigne1;
        v = t->donnees[1]->entierNonSigne1;
        b = t->donnees[2]->entierNonSigne1;
        
        nom = t->donnees[3]->chaine.texte;
        
        j->r = r;
        j->v = v;
        j->b = b;
        j->nom = nom;
        
           /*   Création de l'id du joueur  */ 
        j->id = ++nbJoueursInscrits;
        
        trameReg = creer_trame_registered_ok(j->id);
    }
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameReg);
       /*  debug  */ 
    
    envoyer_trame(sock, trameReg);
    
    return j;
}

   /*   Envoi aux clients  */ 
   /*  @todo modifier  */ 
int envoyer_user(SOCKET sock, Joueur j) {
    Trame trameUser = creer_trame_user(j);
    int error = envoyer_trame(sock, trameUser);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameUser);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_users(SOCKET sock, Joueurs lesJoueurs) {
       /*  @todo nombre de joueurs ?  */ 
       /*  int nbJoueurs = sizeof(*j) / sizeof(Joueur);  */ 
    int i = 0;
    int error;
    
    while (i < lesJoueurs->nbJoueurs) {
        if(envoyer_user(sock, lesJoueurs->joueur[i]) == ERROR) {
            return ERROR;
        }
        i++;
    }
       
    error = envoyer_end(sock, lesJoueurs);
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_end(SOCKET sock, Joueurs lesJoueurs) {
    Trame trameEnd = creer_trame_end();
    int error = envoyer_trame(sock, trameEnd);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameEnd);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_pause(SOCKET sock, const char* message, Joueurs lesJoueurs) {
    Trame tramePause = creer_trame_pause(message);
    int error = envoyer_trame(sock, tramePause);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(tramePause);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_start(SOCKET sock, const char* message, Joueurs lesJoueurs) {
    Trame trameStart = creer_trame_start(message);
    int error = envoyer_trame(sock, trameStart);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameStart);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_turn(SOCKET sock, Joueurs lesJoueurs) {
       /*  @todo gerer le temps  */ 
    Trame trameTurn = creer_trame_turn(0, lesJoueurs);
    int error = envoyer_trame(sock, trameTurn);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameTurn);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_death(SOCKET sock, unsigned short id, Joueurs lesJoueurs) {
    Trame trameDeath = creer_trame_death(id);
    int error = envoyer_trame(sock, trameDeath);
    
       /*   Desinscription du joueur  */ 
    set_inscription_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameDeath);
       /*  debug  */ 
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_deaths(SOCKET sock, unsigned short id1, 
                                unsigned short id2, Joueurs lesJoueurs) {
    Trame trameDeath = creer_trame_deaths(id1, id2);
    int error = envoyer_trame(sock, trameDeath);
    
       /*   Deconnexion des 2 joueurs  */ 
    set_inscription_joueur(get_joueur_par_id(id1, lesJoueurs), 0);
    set_inscription_joueur(get_joueur_par_id(id2, lesJoueurs), 0);
    
       /*  debug  */ 
    printf("#Serveur : ");
    afficher_trame(trameDeath);
       /*  debug  */ 
    
    return error;
}