#include "builder.h"
#include "protocole.h"

Trame creer_trame_ack(int ok) {
    Trame trameAck = creer_trame(Ack);
    
    Donnee chaineOk = creer_chaine("OK");
    Donnee chaineNo = creer_chaine("NO");
    Donnee chaineNomVersion = creer_chaine(NOM_VERSION_PROTOCOLE);
    
    if(ok) {
        ajouter_donnee(&trameAck, chaineOk); 
    } else {
        ajouter_donnee(&trameAck, chaineNo);
    }
    
    ajouter_donnee(&trameAck, chaineNomVersion);
    
    return trameAck;
}

Trame creer_trame_registered_ok(unsigned short id) {
    Trame trameRegOk = creer_trame(Registered);
    Donnee ok = creer_chaine("OK");
    Donnee dId = creer_entierNonSigne2(id);
    
    ajouter_donnee(&trameRegOk, ok);
    ajouter_donnee(&trameRegOk, dId);
    
    return trameRegOk;
}

Trame creer_trame_registered_no(char* message) {
    Trame trameRegNo = creer_trame(Registered);
    Donnee no = creer_chaine("NO");
    Donnee  msgErr = creer_chaine(message);
    
    ajouter_donnee(&trameRegNo, no);
    ajouter_donnee(&trameRegNo, msgErr);
    
    return trameRegNo;
}

Trame creer_trame_user(Joueur j) {
    Trame trameUser = creer_trame(User);
    Donnee id = creer_entierNonSigne2(j.id);
    Donnee nom = creer_chaine(j.nom);
    Donnee r = creer_entierNonSigne1(j.r);
    Donnee v = creer_entierNonSigne1(j.v);
    Donnee b = creer_entierNonSigne1(j.b);
    
    Donnee x0 = creer_entierNonSigne2(j.x);
    Donnee y0 = creer_entierNonSigne2(j.y);
    Donnee dir = creer_entierNonSigne1(j.dir);
    Donnee speed = creer_entierNonSigne1(j.speed);
    
    ajouter_donnee(&trameUser, id);
    ajouter_donnee(&trameUser, nom);
    ajouter_donnee(&trameUser, r);
    ajouter_donnee(&trameUser, v);
    ajouter_donnee(&trameUser, b);
    
    ajouter_donnee(&trameUser, x0);
    ajouter_donnee(&trameUser, y0);
    ajouter_donnee(&trameUser, dir);
    ajouter_donnee(&trameUser, speed);
    
    return trameUser;
}

Trame creer_trame_win(unsigned short id) {
    Trame trameWin = creer_trame(Win);
    
    Donnee dId = creer_entierNonSigne2(id);
    ajouter_donnee(&trameWin, dId);
    
    return trameWin;
}

// Un participant meurt
Trame creer_trame_death(unsigned short id1) {
    Trame trameDeath = creer_trame(Death);
    //int nbIds = sizeof(id) / sizeof(short);
    Donnee id;

    id = creer_entierNonSigne2(id1);
    ajouter_donnee(&trameDeath, id);
    
    return trameDeath;    
}

// Personne ne gagne (collision entre deux survivants)
Trame creer_trame_deaths(unsigned short id1, unsigned short id2) {
    Trame trameDeath = creer_trame(Death);
    //int nbIds = sizeof(id) / sizeof(short);
    Donnee id;
    
    id = creer_entierNonSigne2(id1);
    ajouter_donnee(&trameDeath, id);
    
    id = creer_entierNonSigne2(id2);
    ajouter_donnee(&trameDeath, id);

    return trameDeath;    
}

Trame creer_trame_pause(char* message) {
    Trame tramePause = creer_trame(Pause);
    Donnee chaine = creer_chaine(message);
    ajouter_donnee(&tramePause, chaine);
    
    return tramePause;
}

Trame creer_trame_start(char* message) {
    Trame trameStart = creer_trame(Start);
    Donnee chaine = creer_chaine(message);
    ajouter_donnee(&trameStart, chaine);
    
    return trameStart;
}
Trame creer_trame_turn(unsigned int t, Joueur j[]) {
    Trame trameTurn = creer_trame(Turn);
    Donnee id, x, y, dir;
    int nbJoueurs = sizeof(j) / sizeof(Joueur);
    int i;
    
    for(i=0; i < nbJoueurs; i++) {
        id = creer_entierNonSigne2(j[i].id);
        x = creer_entierNonSigne2(j[i].x);
        y = creer_entierNonSigne2(j[i].y);
        dir = creer_entierNonSigne2(j[i].dir);
        
        ajouter_donnee(&trameTurn, id);
        ajouter_donnee(&trameTurn, x);
        ajouter_donnee(&trameTurn, y);
        ajouter_donnee(&trameTurn, dir);
    }
    
    return trameTurn;
}

Trame creer_trame_end() {
    Trame trameEnd = creer_trame(End);
    return trameEnd;
}