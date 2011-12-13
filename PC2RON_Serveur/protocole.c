#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocole.h"
#include "erreur.h"
#include "builder.h"
#include "reception.h"
#include "envoi.h"

/*
 @todo
 * check_connect_frame(Frame frame)
 * check_initiate_frame(Frame frame)
 * check_order_frame(Frame frame)
 * 
 * check_frame(Frame frame)
 * 
 * respond_frame
 * respond_initiate_frame
 * respond_connect_frame
 * respond_order_frame
 */
/* Nombre courant de joueurs connectes */ 
static unsigned short nbJoueursConnectes = 0;
static unsigned short nbJoueursInscrits = 0;

/*   Requetes du client  */ 
char* get_order(int sock, Trame t, Joueurs lesJoueurs) {
    unsigned char* o = NULL;
    
    Joueur j = get_joueur_par_sock(sock, lesJoueurs);
    
    /*   Un joueur ne peut envoyer d'ordre que s'il est inscrit  */ 
    if (j == NULL || !(j->estInscrit)) {
        PRINT_NOT_REGISTERED(sock);
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
Resultat* get_resultat_echange(int sock, Joueurs lesJoueurs) {
    Joueur j;
    char* o;
    int resultatInitiate = 0;
    Resultat* res = (Resultat*) malloc(sizeof(Resultat));
    Trame trameRecue = recevoir_trame(sock);
       /*  recevoir_trame(sock, &trameRecue);  */ 
    
    /* Trame recue non correcte */
    if(trameRecue == NULL) {
        free(res);
        return NULL;
    }
    
    /*  debug  */ 
    printf("<<< ");
    afficher_trame(trameRecue);
    /* debug */
    
    /*  @todo modifier Deconnexion du joueur  */ 
    if(trameRecue->fanion == TRAME_SPECIALE) {
        deconnecter_joueur(get_joueur_par_sock(sock, lesJoueurs));
        res->typeTrame = NOT_CONNECTED;
        res->contenu = NULL;
 
        return res;
    }
    
    switch(trameRecue->id) {      
        case Connect:
            j = repondre_connect(sock, trameRecue, lesJoueurs);
            if(j != NULL) {
                res = malloc(sizeof(Resultat));
                res->typeTrame = Connect;
                res->contenu = j;    
            }
            break;
        
        case Initiate:
            resultatInitiate = repondre_initiate(sock, trameRecue, lesJoueurs);
            if(resultatInitiate == SUCCESS) {
                res = malloc(sizeof(Resultat));
                res->contenu = NULL;
                res->typeTrame = Initiate;
            }
            break;
        
        case Order:
            o = get_order(sock, trameRecue, lesJoueurs);
            if(o != NULL) {
                res = malloc(sizeof(Resultat));
                res->typeTrame = Order;
                res->contenu = o;
            }
            break;
        
        default:
            /*@todo envoyer un message d'erreur au client*/
            PRINT_UNKNOWN_FRAME_TYPE(trameRecue->id);
            break;
    }
    
    free_trame(trameRecue);
    
    return res;
}

   /*   Reponses au client  */ 
int repondre_initiate(int sock, Trame t, Joueurs lesJoueurs) {
    Joueur j = get_joueur_par_sock(sock, lesJoueurs);
    
    /*  char* sAppName, sAppVersion;  */ 
    int error = ERROR;
    
    /*   init de la trame à renvoyer par un ack negatif  */ 
    Trame trameAck = creer_trame_ack(0);
    
    /*debug*/
    printf("nbJoueursConnectes = %d\n", nbJoueursConnectes);
    printf("lesJoueurs->nbJoueurs = %d\n", lesJoueurs->nbJoueurs);
    
       /*  @todo un joueur ne peut pas se connecter plus d'une fois  */ 
    if (j != NULL && j->estConnecte) {
        PRINT_ALREADY_CONNECTED(j->sock);
    }
    
    else if(nbJoueursConnectes >= lesJoueurs->nbJoueurs) {
        PRINT_LIMIT_PLAYERS_CONNECTED_REACHED();
    
    /* Verification de la trame Init recue */ 
    /*@todo creer fonction verifier_trame_init */   
        
    } else if(t->nbDonnees != 2) {
        PRINT_WRONG_DATA_SIZE(sock, S_INITIATE);
        
    } else if(t->donnees[0]->type != CHAINE ||
        t->donnees[1]->type != CHAINE) {
        PRINT_WRONG_FORMAT(S_INITIATE);
        
    } else {
        
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
            error = SUCCESS;
            lesJoueurs->joueur[nbJoueursConnectes]->sock = sock;
            lesJoueurs->joueur[nbJoueursConnectes]->estConnecte = 1;
            nbJoueursConnectes++;
            free_trame(trameAck);
            trameAck = creer_trame_ack(1);
        }
    }
    
    /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameAck);
    /*  debug  */ 
    
    envoyer_trame(sock, trameAck);
    free_trame(trameAck);
    
    return error;
}

Joueur repondre_connect(int sock, Trame t, Joueurs lesJoueurs) {   
    Trame trameReg;
    Joueur j = NULL;
    Joueur j2 = NULL;
    
    unsigned char r, v, b;
    char* nom;
    
       /*  @todo Un joueur doit etre connecte pour s'inscrire  */ 
    j2 = get_joueur_par_sock(sock, lesJoueurs);
    
    if (j2 == NULL || !(j2->estConnecte)) {
        trameReg = creer_trame_registered_no(S_NOT_CONNECTED);
    
       /*  @todo Un joueur ne peut pas s'inscrire plus d'une fois  */ 
    } else if (j2 != NULL && j2->estInscrit) {
        trameReg = creer_trame_registered_no(S_ALREADY_CONNECTED);
    
    /*@todo creer fonction verifier_trame_connect */
    } else if(t->nbDonnees != 4) {
        trameReg = creer_trame_registered_no(S_WRONG_FRAME_FORMAT);
           /*  fprintf(stderr, MSG_ERR_TRAME);  */ 
        
    } else if(t->donnees[0]->type != ENTIER_NON_SIGNE1 ||
            t->donnees[1]->type != ENTIER_NON_SIGNE1 ||
            t->donnees[2]->type != ENTIER_NON_SIGNE1) {
        trameReg = creer_trame_registered_no(S_WRONG_RGB_FORMAT);
        
    } else if(t->donnees[3]->type != CHAINE) {
        trameReg = creer_trame_registered_no(S_WRONG_NAME_FORMAT);
        
    } else {
           /*  j = malloc(sizeof(Joueur));  */ 
        j = get_joueur_par_sock(sock, lesJoueurs);
        j->estInscrit = 1;
        
           /*   Reponse a la requete Connect  */ 
        r = t->donnees[0]->entierNonSigne1;
        v = t->donnees[1]->entierNonSigne1;
        b = t->donnees[2]->entierNonSigne1;
        
        nom = t->donnees[3]->chaine.texte;
        
        j->couleur.r = r;
        j->couleur.v = v;
        j->couleur.b = b;
        j->nom = nom;
        
           /*   Création de l'id du joueur  */ 
        j->id = ++nbJoueursInscrits;
        
        trameReg = creer_trame_registered_ok(j->id);
    }
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameReg);
       /*  debug  */ 
    
    envoyer_trame(sock, trameReg);
    
    free_trame(trameReg);
    
    return j;
}

   /*   Envoi aux clients  */ 
   /*  @todo modifier  */ 
int envoyer_user(int sock, Joueur j) {
    Trame trameUser = creer_trame_user(j);
    int error = envoyer_trame(sock, trameUser);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameUser);
       /*  debug  */ 
    
    free_trame(trameUser);
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_users(int sock, Joueurs lesJoueurs) {
       /*  @todo nombre de joueurs ?  */ 
       /*  int nbJoueurs = sizeof(*j) / sizeof(Joueur);  */ 
    size_t i = 0;
    
    while (i < lesJoueurs->nbJoueurs) {
        if(envoyer_user(sock, lesJoueurs->joueur[i]) == ERROR) {
            return ERROR;
        }
        i++;
    }
    
    return envoyer_end(sock, lesJoueurs);
}

   /*  @todo modifier  */ 
int envoyer_end(int sock, Joueurs lesJoueurs) {
    Trame trameEnd = creer_trame_end();
    int error = envoyer_trame(sock, trameEnd);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameEnd);
       /*  debug  */ 
    
    free_trame(trameEnd);
    return error;
}

   /*  @todo modifier  */ 
int envoyer_pause(int sock, const char* message, Joueurs lesJoueurs) {
    Trame tramePause = creer_trame_pause(message);
    int error = envoyer_trame(sock, tramePause);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(tramePause);
       /*  debug  */ 
    
    free_trame(tramePause);
    return error;
}

   /*  @todo modifier  */ 
int envoyer_start(int sock, const char* message, Joueurs lesJoueurs) {
    Trame trameStart = creer_trame_start(message);
    int error = envoyer_trame(sock, trameStart);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameStart);
       /*  debug  */ 
    
    free_trame(trameStart);
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_turn(int sock, Joueurs lesJoueurs) {
       /*  @todo gerer le temps  */ 
    Trame trameTurn = creer_trame_turn(0, lesJoueurs);
    int error = envoyer_trame(sock, trameTurn);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameTurn);
       /*  debug  */ 
    
    free_trame(trameTurn);
    
    return error;
}

   /*  @todo modifier  */ 
int envoyer_death(int sock, unsigned short id, Joueurs lesJoueurs) {
    Trame trameDeath = creer_trame_death(id);
    int error = envoyer_trame(sock, trameDeath);
    
       /*   Desinscription du joueur  */
    Joueur j = get_joueur_par_sock(sock, lesJoueurs);
    deconnecter_joueur(j);
    error = envoyer_fin_transmission(sock);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameDeath);
       /*  debug  */ 
    
    free_trame(trameDeath);
            
    return error;
}

   /*  @todo modifier  */ 
int envoyer_deaths(int sock, unsigned short id1, 
                                unsigned short id2, Joueurs lesJoueurs) {
    Trame trameDeath = creer_trame_deaths(id1, id2);
    int error = envoyer_trame(sock, trameDeath);
    Joueur j1 = get_joueur_par_id(id1, lesJoueurs);
    Joueur j2 = get_joueur_par_id(id2, lesJoueurs);
    
       /*   Deconnexion des 2 joueurs  */ 
    deconnecter_joueur(j1);
    error = envoyer_fin_transmission(j1->sock);
    
    deconnecter_joueur(j2);
    error = envoyer_fin_transmission(j2->sock);
    
       /*  debug  */ 
    printf(">>> ");
    afficher_trame(trameDeath);
       /*  debug  */ 
    
    free_trame(trameDeath);
    
    return error;
}

void deconnecter_joueur(Joueur j) {
    if(j != NULL) {
        j->estConnecte = 0;
        j->estInscrit = 0;
    }
}