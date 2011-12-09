#include "protocole.h"
#include "builder.h"
#include <sys/types.h>


//SOCKET sock = NULL;
//int estConnecte = 0;
//int estInsrit = 0;

// Nombre courant de joueurs inscrits
unsigned short nbJoueurs = 0;

// Requetes du client
Ordre* get_order(SOCKET sock, Trame t) {
    Ordre* o = NULL;
    
    // Verification de la trame Init recue
    if(t.nbDonnees == 1 &&
       t.donnees[0].type == CHAINE) {
        *o = t.donnees[0].chaine.texte;
    } 
       
    return o;
}

// Point d'entree du protocole 
Resultat get_resultat(SOCKET sock) {
    Resultat res = {TYPE_TRAME_INCONNU, NULL};
    Trame trameRecue;
    recevoir_trame(sock, &trameRecue);
    
    switch(trameRecue.id) {      
        case Connect:
            Joueur j = repondre_connect(sock, trameRecue);
            res.contenu = &j;
            res.typeTrame = Connect;
            break;
        
        case Initiate:
            repondre_initiate(sock, trameRecue);
            res.contenu = NULL;
            res.typeTrame = Initiate;
            break;
        
        case Order:
            Ordre o = get_order(sock, trameRecue);
            if(o != NULL) {
                res.contenu = &o;
                res.typeTrame = Order;
            }
            break;
        
        default:
            //res.contenu = NULL;
            //res.typeTrame = TYPE_TRAME_INCONNU;
            break;
    }
    
    return res;
}

// Reponses au client
ERR_PROTOCOLE repondre_initiate(SOCKET sock, Trame t) {
    ERR_PROTOCOLE erreur = -1;
    
    // init de la trame à renvoyer par un ack negatif
    Trame trameAck = creer_trame_ack(0);
    
    // Verification de la trame Init recue
    if(t.nbDonnees != 2) {
        erreur = ERR_INITIATE;
    } 
    
    else if(t.donnees[0].type != CHAINE ||
       t.donnees[1].type != CHAINE) {
        erreur = ERR_INITIATE;
    } 
    
    else {
        // Reponse a la requete Init
        char* nomAppli = t.donnees[0].chaine.texte;
        char* nomVersion = t.donnees[1].chaine.texte;

        if(strcmp(nomAppli, NOM_APPLICATION) != 0) {
            erreur =  ERR_INITIATE;
        }

        if(strcmp(nomVersion, NOM_VERSION_PROTOCOLE) != 0) {
            erreur = ERR_INITIATE;
        }

        trameAck = creer_trame_ack(1);
    }
    
    envoyer_trame(sock, trameAck);
}

Joueur repondre_connect(SOCKET sock, Trame t) {   
    Trame trameReg;
    Joueur j;
    
    // @todo Verification du quota de joueurs

    // Verification de la trame Init recue
    if(t.nbDonnees != 4) {
        trameReg = creer_trame_registered_no(MSG_ERR_TRAME);
    } 
    
    else if(t.donnees[0].type != ENTIER_NON_SIGNE1 ||
            t.donnees[1].type != ENTIER_NON_SIGNE1 ||
            t.donnees[2].type != ENTIER_NON_SIGNE1) {
        trameReg = creer_trame_registered_no(MSG_ERR_RVB);
    } 
    
    else if(t.donnees[3].type != CHAINE) {
        trameReg = creer_trame_registered_no(MSG_ERR_NOM);
    } else {
        // Reponse a la requete Connect
        unsigned char r = t.donnees[0].entierNonSigne1;
        unsigned char v = t.donnees[1].entierNonSigne1;
        unsigned char b = t.donnees[2].entierNonSigne1;
        
        char* nom = t.donnees[3].chaine;
        
        j.r = r;
        j.v = v;
        j.b = b;
        j.nom = nom;
        
        // Création de l'id du joueur
        j.id = ++nbJoueurs;
        
        trameReg = creer_trame_registered_ok(j.id);
    }
    
    envoyer_trame(sock, trameReg);
}

// Envoi aux clients
ERR_PROTOCOLE envoyer_user(Joueur j) {
    Trame trameUser = creer_trame_user(j);
    envoyer_trame(sock, trameUser);
}

ERR_PROTOCOLE envoyer_users(Joueur j[]) {
    int nbJoueurs = sizeof(j) / sizeof(Joueur);
    int i;
    
    for(i=0; i < nbJoueurs; i++) {
        envoyer_user(j[i]);
    }
    
    envoyer_end();
}

ERR_PROTOCOLE envoyer_end(SOCKET sock) {
    Trame trameEnd = creer_trame_end();
    envoyer_trame(sock, trameEnd);
}

ERR_PROTOCOLE envoyer_pause(SOCKET sock, char* message) {
    Trame tramePause = creer_trame_pause(message);
    envoyer_trame(sock, tramePause);
}

ERR_PROTOCOLE envoyer_start(char* message) {
    Trame trameStart = creer_trame_pause(message);
    envoyer_trame(sock, trameStart);
}

ERR_PROTOCOLE envoyer_turn(Joueur j[]) {
    Trame trameTurn = creer_trame_turn(j);
    envoyer_trame(sock, trameTurn);
}