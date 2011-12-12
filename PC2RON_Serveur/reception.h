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
    
Trame* recevoir_trame(SOCKET sock);
Donnee* recevoir_donnee(SOCKET sock);
Donnee* recevoir_entierSigne1(SOCKET sock);
Donnee* recevoir_entierSigne2(SOCKET sock);
Donnee* recevoir_entierSigne4(SOCKET sock);
Donnee* recevoir_entierNonSigne1(SOCKET sock);
Donnee* recevoir_entierNonSigne2(SOCKET sock);
Donnee* recevoir_entierNonSigne4(SOCKET sock);
Donnee* recevoir_chaine(SOCKET sock);
Donnee* recevoir_flottant(SOCKET sock);

#ifdef	__cplusplus
}
#endif

#endif	/* RECEPTION_H */

