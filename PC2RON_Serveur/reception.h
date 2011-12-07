/* 
 * File:   reception.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:38
 */

#ifndef RECEPTION_H
#define	RECEPTION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"
    
ERREUR_TRAME recevoir_trame(SOCKET sock, Trame* trameRecue);
ERREUR_DONNEE recevoir_donnee(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne1(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne2(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierSigne4(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne1(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne2(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_entierNonSigne4(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_chaine(SOCKET sock, Donnee* donneeRecue);
ERREUR_DONNEE recevoir_flottant(SOCKET sock, Donnee* donneeRecue);

#ifdef	__cplusplus
}
#endif

#endif	/* RECEPTION_H */

