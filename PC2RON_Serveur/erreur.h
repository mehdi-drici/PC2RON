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
    
// Messages d'erreur pour la trame Registered (Client)
#define WRONG_FRAME_FORMAT "Le format de la trame n'est pas correct"
#define WRONG_RGB_FORMAT "Le format RVB n'est pas correct"
#define WRONG_NAME_FORMAT "Le nom doit etre une chaine de caracteres"
#define NOT_CONNECTED "Vous n'etes pas connecte"
#define ALREADY_CONNECTED "Vous etes deja connecte"
#define LIMIT_PLAYERS_REGISTERED_REACHED "Le quota de joueurs inscrits a ete atteint"
    
// Messages d'erreur pour le serveur
#define PRINT_UNSUPPORTED_VERSION(sVersion) \
    fprintf(stderr, "La version %s n'est pas supportee\n", sVersion);

#define PRINT_WRONG_APPNAME(sAppName) \
    fprintf(stderr, "Le nom de l'application '%s' n'est pas correct\n", sAppName);

#define PRINT_WRONG_FORMAT(sFrameName) \
    fprintf(stderr, "Le format de la trame %s n'est pas correct\n", sFrameName);
    
#define PRINT_CONNECT_ERROR(sock) \
    fprintf(stderr, "Problème d'inscription du joueur lie a la socket %d", sock);

#define PRINT_ORDER_ERROR(sock) \
    fprintf(stderr, "L'ordre reçu par le joueur lie a la socket %d n'est pas correct\n", sock);
    
#define PRINT_UNKNOWN_FRAME_TYPE(byteFrametype)  \
    fprintf(stderr, "Le type de la trame reçue est inconnu %2.2X\n", byteFrametype);

#define PRINT_ALREADY_CONNECTED(player) \
    fprintf(stderr, "Le joueur lie a la socket %d est deja connecte\n", player->sock);

#define PRINT_ALREADY_REGISTERED(player) \
    fprintf(stderr, "Le joueur %s (id: %d) est deja inscrit\n", player->nom, player->id);

#define PRINT_WRONG_DATA_SIZE(sock, sFrametype) \
    fprintf(stderr, "Le nombre de donnees de la trame %s recue par la socket %d \
                     n'est pas correcte\n", sFrametype, sock);
    
#define EXIT_IF_ERROR_RECV_DATA(p_sock, p_iNbBytes, data) \
        if (p_iNbBytes < 0) { \
            close (p_sock); \
            perror(__func__); \
            free(data); \
            exit(errno); \
            return NULL;  \
        } else if (p_iNbBytes == 0) { \
            close (p_sock); \
            fprintf(stderr, "%s >> %s: Deconnexion brutale \
            du joueur (socket: %d)\n", \
            __FILE__, __func__, p_sock); \
            free(data); \
            return NULL; \
        };
 
#define EXIT_IF_ERROR_RECV_FRAME(p_sock, p_iNbBytes, frame) \
        if (p_iNbBytes < 0) { \
                close (p_sock); \
                perror(__func__); \
                free_trame(frame); \
                exit(errno); \
                return NULL;  \
        } else if (p_iNbBytes == 0) { \
            close (p_sock); \
            fprintf(stderr, "%s >> %s: Deconnexion brutale \
            du client (socket: %d)\n", \
            __FILE__, __func__, p_sock); \
            free_trame(frame); \
            return NULL; \
        };

#define EXIT_IF_ERROR_SEND(p_sock, p_iNbBytes) \
    if (p_iNbBytes < 0) { \
        close (p_sock); \
        perror(__func__); \
        exit(errno); \
        return ERROR;  \
    } else if (p_iNbBytes == 0) { \
        close (p_sock); \
        fprintf(stderr, "%s >> %s: Deconnexion brutale \
        du client (socket: %d)\n", \
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

