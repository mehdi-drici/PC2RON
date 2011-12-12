/* 
 * File:   factory.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:39
 */

#ifndef FACTORY_H
#define	FACTORY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"
    
/* Création d'une trame ou d'une donnée */
Trame creer_trame(unsigned char id);
Donnee creer_entierSigne1(char entier);
Donnee creer_entierSigne2(short entier);
Donnee creer_entierSigne4(long entier);
Donnee creer_entierNonSigne1(unsigned char entier);
Donnee creer_entierNonSigne2(unsigned short entier);
Donnee creer_entierNonSigne4(unsigned long entier);
Donnee creer_chaine(char texte[]);
Donnee creer_flottant(double flottant);

#ifdef	__cplusplus
}
#endif

#endif	/* FACTORY_H */

