#include <sys/types.h>
#include "protocole.h"

// Nombre courant de joueurs inscrits
unsigned short nbJoueursInscrits = 0;
int nbMaxJoueurs = 0;
Joueurs lesJoueurs;

void init_protocole(Joueurs j) {
    lesJoueurs = j;
}

// Requetes du client
char* get_order(SOCKET sock, Trame t) {
    unsigned char* o = NULL;
    
    Joueur* j = get_joueur_par_sock(sock, lesJoueurs);
    
    // Un joueur ne peut envoyer d'ordre que s'il est inscrit
    if (j != NULL && !(j->estInscrit)) {
        fprintf(stderr, "Le joueur avec la socket %d n'est pas inscrit !\n", sock);
    }
    
    // Verification de la trame Init recue
    else if(t.nbDonnees == 1 &&
       t.donnees[0].type == CHAINE) {
        o = t.donnees[0].chaine.texte;
    } 
    
    return o;
}

// Point d'entree du protocole 
// Si resultat NULL Alors il y'a eu une erreur lors de l'échange
// qui sera redirigée dans le flux d'erreurs
Resultat* get_resultat_echange(SOCKET sock) {
    Joueur* j;
    char* o;
    Resultat* res = NULL;
    Trame trameRecue;
  
    recevoir_trame(sock, &trameRecue);
    
    printf("Type trame recue = %d\n", trameRecue.fanion);
    //debug
    printf("#Client : ");
    afficher_trame(trameRecue);
    //debug
    
    //@todo Deconnexion du joueur
    if(trameRecue.fanion == TRAME_SPECIALE) {
        //debug @todo deconnexion de la socket
        printf("Deconnexion du joueur !\n");
        //debug
        
        //Deconnexion du joueur
        set_connexion_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        set_inscription_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
        
        return res;
    }
        
    switch(trameRecue.id) {      
        case Connect:
            j = repondre_connect(sock, trameRecue);
            
            if(j != NULL) {
                res = malloc(sizeof(Resultat));
                res->typeTrame = Connect;
                res->contenu = j;    
            } else {
                fprintf(stderr, MSG_ERR_CONNECT(sock));
                //res.erreur = ERR_CONNECT;
                //res.msgErr = MSG_ERR_CONNECT(sock);
            }
            break;
        
        case Initiate:
            repondre_initiate(sock, trameRecue);
            res = malloc(sizeof(Resultat));
            res->contenu = NULL;
            res->typeTrame = Initiate;
            break;
        
        case Order:
            o = get_order(sock, trameRecue);
            res = malloc(sizeof(Resultat));
            res->typeTrame = Order;
            if(o != NULL) {
                res->contenu = o;
            } else {
                //fprintf(stderr, MSG_ERR_ORDER(sock));
                //res.erreur = ERR_ORDER;
                //res.msgErr = MSG_ERR_ORDER(sock);
            }
            break;
        
        default:
            //res.erreur = ERR_TYPE_INCONNU;
            //res.typeTrame = -1;
            //res.msgErr = MSG_ERR_TYPE_INCONNU;
            break;
    }
    
    return res;
}

// Reponses au client
ERR_PROTOCOLE repondre_initiate(SOCKET sock, Trame t) {
    ERR_PROTOCOLE erreur = -1;
    Joueur* j = get_joueur_par_sock(sock, lesJoueurs);
    
    // init de la trame à renvoyer par un ack negatif
    Trame trameAck = creer_trame_ack(0);
    
    //@todo un joueur ne peut pas se connecter plus d'une fois
    if (j != NULL && j->estConnecte) {
        fprintf(stderr, "Le joueur avec la socket %d est deja connecte !", sock);
    }
    
    // Verification de la trame Init recue
    else if(t.nbDonnees != 2) {
        erreur = ERR_INITIATE;
        fprintf(stderr, "La trame Init recue n'est pas correcte");
    } 
    
    else if(t.donnees[0].type != CHAINE ||
       t.donnees[1].type != CHAINE) {
        erreur = ERR_INITIATE;
        fprintf(stderr, "La trame Init recue n'est pas correcte");
    } 
    
    else {
        // Reponse a la requete Init
        char* nomAppli = t.donnees[0].chaine.texte;
        // On enlève le '?'
        nomAppli[strlen(nomAppli) - 1] = '\0';
        
        char* nomVersion = t.donnees[1].chaine.texte;
        
        if(strcmp(nomAppli, NOM_APPLICATION) != 0) {
            erreur =  ERR_INITIATE;
            fprintf(stderr, "Le nom de l'application n'est pas correct");
        }

        else if(strcmp(nomVersion, NOM_VERSION_PROTOCOLE) != 0) {
            erreur = ERR_INITIATE;
            fprintf(stderr, "La version du protocole n'est pas supportee");
        }

        else {
            set_connexion_joueur(get_joueur_par_sock(sock, lesJoueurs), 1);
            trameAck = creer_trame_ack(1);
        }
    }
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameAck);
    //debug
    
    envoyer_trame(sock, trameAck);
    
    return erreur;
}

Joueur* repondre_connect(SOCKET sock, Trame t) {   
    Trame trameReg;
    Joueur* j = NULL;
    Joueur* j2 = NULL;
    
    unsigned char r, v, b;
    char* nom;
    
    //@todo Un joueur doit etre connecte pour s'inscrire
    j2 = get_joueur_par_sock(sock, lesJoueurs);
    if (j2 != NULL && !(j2->estConnecte)) {
        trameReg = creer_trame_registered_no("Vous n'etes pas connecte");
        fprintf(stderr, "Le joueur avec la socket %d doit etre connecte pour s'inscrire\n", sock);
    }
    
    //@todo Un joueur ne peut pas s'inscrire plus d'une fois
    else if (j2 != NULL && j2->estInscrit) {
        trameReg = creer_trame_registered_no("Vous etes deja inscrit");
        fprintf(stderr, "Le joueur avec la socket %d est deja connecte\n", sock);
    }
    
    
    // @todo Verification du quota de joueurs
    else if(nbJoueursInscrits == lesJoueurs.nbJoueurs) {
        trameReg = creer_trame_registered_no("Le quota de joueurs a ete atteint");
        fprintf(stderr, "Le nombre max de joueurs inscrit a été atteint\n");
    }    
    
    // Verification de la trame Init recue
    else if(t.nbDonnees != 4) {
        trameReg = creer_trame_registered_no(MSG_ERR_TRAME);
        fprintf(stderr, MSG_ERR_TRAME);
    } 
    
    else if(t.donnees[0].type != ENTIER_NON_SIGNE1 ||
            t.donnees[1].type != ENTIER_NON_SIGNE1 ||
            t.donnees[2].type != ENTIER_NON_SIGNE1) {
        trameReg = creer_trame_registered_no(MSG_ERR_RVB);
        fprintf(stderr, MSG_ERR_RVB);
    } 
    
    else if(t.donnees[3].type != CHAINE) {
        trameReg = creer_trame_registered_no(MSG_ERR_NOM);
        fprintf(stderr, MSG_ERR_NOM);
        
    } else {
        //j = malloc(sizeof(Joueur));
        j = get_joueur_par_sock(sock, lesJoueurs);
        
        // Initialisation du joueur
        init_joueur(sock, j);
        
        // Reponse a la requete Connect
        r = t.donnees[0].entierNonSigne1;
        v = t.donnees[1].entierNonSigne1;
        b = t.donnees[2].entierNonSigne1;
        
        nom = t.donnees[3].chaine.texte;
        
        j->r = r;
        j->v = v;
        j->b = b;
        j->nom = nom;
        
        // Création de l'id du joueur
        j->id = ++nbJoueursInscrits;
        
        trameReg = creer_trame_registered_ok(j->id);
    }
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameReg);
    //debug
    
    envoyer_trame(sock, trameReg);
    
    return j;
}

// Envoi aux clients
ERR_PROTOCOLE envoyer_user(SOCKET sock, Joueur j) {
    Trame trameUser = creer_trame_user(j);
    envoyer_trame(sock, trameUser);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameUser);
    //debug
}

ERR_PROTOCOLE envoyer_users(SOCKET sock, Joueur j[]) {
    //@todo nombre de joueurs ?
    int nbJoueurs = sizeof(*j) / sizeof(Joueur);
    int i;
    
    for(i=0; i < nbJoueurs; i++) {
        envoyer_user(sock, j[i]);
    }
    
    envoyer_end(sock);
}

ERR_PROTOCOLE envoyer_end(SOCKET sock) {
    Trame trameEnd = creer_trame_end();
    envoyer_trame(sock, trameEnd);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameEnd);
    //debug
}

ERR_PROTOCOLE envoyer_pause(SOCKET sock, char* message) {
    Trame tramePause = creer_trame_pause(message);
    envoyer_trame(sock, tramePause);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(tramePause);
    //debug
}

ERR_PROTOCOLE envoyer_start(SOCKET sock, char* message) {
    Trame trameStart = creer_trame_start(message);
    envoyer_trame(sock, trameStart);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameStart);
    //debug
}

ERR_PROTOCOLE envoyer_turn(SOCKET sock, Joueur j[]) {
    //@todo gerer le temps
    Trame trameTurn = creer_trame_turn(0, j);
    envoyer_trame(sock, trameTurn);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameTurn);
    //debug
}

ERR_PROTOCOLE envoyer_death(SOCKET sock, unsigned short id) {
    Trame trameDeath = creer_trame_death(id);
    envoyer_trame(sock, trameDeath);
    
    // Deconnexion du joueur
    set_inscription_joueur(get_joueur_par_sock(sock, lesJoueurs), 0);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameDeath);
    //debug
}

ERR_PROTOCOLE envoyer_deaths(SOCKET sock, unsigned short id1, 
                                          unsigned short id2) {
    Trame trameDeath = creer_trame_deaths(id1, id2);
    envoyer_trame(sock, trameDeath);
    
    // Deconnexion des 2 joueurs
    set_inscription_joueur(get_joueur_par_id(id1, lesJoueurs), 0);
    set_inscription_joueur(get_joueur_par_id(id2, lesJoueurs), 0);
    
    //debug
    printf("#Serveur : ");
    afficher_trame(trameDeath);
    //debug
}