#include "protocole.h"

// Requetes du client
Ordre get_order(Trame t);

// Reponses au client
ERR_PROTOCOLE repondre_initiate(Trame t);
Joueur repondre_connect(Trame t);

// Envoi aux clients
ERR_PROTOCOLE envoyer_user(Joueur j) {
    
}

ERR_PROTOCOLE envoyer_users(Joueur j[]);
ERR_PROTOCOLE envoyer_end();
ERR_PROTOCOLE envoyer_pause(char* message);
ERR_PROTOCOLE envoyer_start(char* message);
ERR_PROTOCOLE envoyer_turn(Joueur j[]);