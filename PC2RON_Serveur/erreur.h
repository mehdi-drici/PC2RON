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
#define ERROR -1
#define SUCCESS 0
            
#define EXIT_IF_ERROR_RECV_DATA(p_sock, p_iNbBytes, data) if (p_iNbBytes < 0) { \
                                        close (p_sock); \
                                        perror("%s", __func__); \
                                        free(data); \
                                        exit(errno); \
                                        return NULL;  \
                                      } else if (p_iNbBytes == 0) { \
                                        close (p_sock); \
                                        fprintf("%s >> %s: Deconnexion brutale \
                                        du joueur (socket: %d)\n", \
                                        __FILE__, __func__, p_sock); \
                                        free(data); \
                                        return NULL; \
                                      };
 
#define EXIT_IF_ERROR_RECV_FRAME(p_sock, p_iNbBytes, frame) if (p_iNbBytes < 0) { \
                                        close (p_sock); \
                                        perror("%s", __func__); \
                                        free_trame(frame); \
                                        exit(errno); \
                                        return NULL;  \
                                      } else if (p_iNbBytes == 0) { \
                                        close (p_sock); \
                                        fprintf("%s >> %s: Deconnexion brutale \
                                        du joueur (socket: %d)\n", \
                                        __FILE__, __func__, p_sock); \
                                        free_trame(frame); \
                                        return NULL; \
                                      };

#define EXIT_IF_ERROR_SEND(p_sock, p_iNbBytes) if (p_iNbBytes < 0) { \
                                        close (p_sock); \
                                        perror("%s", __func__); \
                                        exit(errno); \
                                        return ERROR;  \
                                      } else if (p_iNbBytes == 0) { \
                                        close (p_sock); \
                                        fprintf("%s >> %s: Deconnexion brutale \
                                        du joueur (socket: %d)\n", \
                                        __FILE__, __func__, p_sock); \
                                        return ERROR; \
                                      };
    
#define PRINT_UNKNOWN_PENNANT(fanion) fprintf(stderr, "%s >> %s : Le fanion %2.2x est \
                                                  inconnu\n", __FILE__, __func__, fanion);
#define PRINT_UNKNOWN_DATA_TYPE(datatype) fprintf(stderr, "%s >> %s : Le type de donnee %2.2x \
                                       est inconnu\n", __FILE__, __func__, datatype); 
    
#ifdef	__cplusplus
}
#endif

#endif	/* ERREUR_H */

