/* 
 * File:   erreur.h
 * Author: mehdi
 *
 * Created on 11 décembre 2011, 20:10
 */

#ifndef ERREUR_H
#define	ERREUR_H

#ifdef	__cplusplus
extern "C" {
#endif

// Code d'échec et de réussite d'une fonction
#define ERREUR -1
#define SUCCES 0
    
#define AFF_ERR(msg) fprintf("%s >> %s: %s\n", __FILE__, __func__, msg);
#define AFF_ERR_TYPE_DONNEE(type) fprintf("%s >> %s: Le type de donnee %2.2x \
                                       est inconnu\n", __FILE__, __func__, msg);
#define AFF_ERR_ENVOI_ENTETE(typeDonnee) fprintf("%s >> %s: Erreur d'envoi \
                               d'entete du type %s\n", __FILE__, __func__, msg);
#define AFF_ERR_ENVOI_ENTETE_TRAME() fprintf("%s >> %s: Erreur d'envoi \
                               d'entete d'une trame\n", __FILE__, __func__);
#define AFF_ERR_ENVOI_VALEUR(typeDonnee) fprintf("%s >> %s: Erreur d'envoi de \
                              la valeur du type %s\n", __FILE__, __func__, msg);
#define AFF_ERR_RCPT_DONNEE() fprintf("%s >> %s: Erreur de reception \
                             de la donnee\n", __FILE__, __func__);
#define AFF_ERR_RCPT_ENTETE(typeDonnee) fprintf("%s >> %s: Erreur de reception \
                               d'entete du type %s\n", __FILE__, __func__, msg);
#define AFF_ERR_RCPT_VALEUR(typeDonnee) fprintf("%s >> %s: Erreur d'envoi de la\
                                 valeur du type %s\n", __FILE__, __func__, msg);    
    
#ifdef	__cplusplus
}
#endif

#endif	/* ERREUR_H */

