/* 
 * File:   envoi.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:38
 */

#ifndef ENVOI_H
#define	ENVOI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"

/* Envoi d'une trame */
ERREUR_TRAME envoyer_trame(SOCKET sock, Trame trameEnvoyee);
//char** convertir_trame_toBytes(Trame trame);
ERREUR_DONNEE envoyer_donnee(SOCKET sock, Donnee donnee);
ERREUR_DONNEE envoyer_entierSigne1(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierSigne2(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierSigne4(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne1(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne2(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_entierNonSigne4(SOCKET sock, Donnee entier);
ERREUR_DONNEE envoyer_chaine(SOCKET sock, Donnee chaine);
ERREUR_DONNEE envoyer_flottant(SOCKET sock, Donnee flottant);

#ifdef	__cplusplus
}
#endif

#endif	/* ENVOI_H */

