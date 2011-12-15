#include <errno.h>
#include "serveur.h"
#include <unistd.h>

#define NB_MAX_CLIENTS 10

/**
 * Etablissement de la connexion du serveur
 * @return 
 */
int connect_server() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    int valeur_option = 1;

    /* Création de la socket */
    if(sock == INVALID_SOCKET) {
        perror("socket()");
        exit(errno);
    }

    /* Création de l'interface */
    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

       /*   lose the pesky "Address already in use" error message  */ 
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &valeur_option, sizeof(int)) == -1) {
        pthread_exit(NULL);
    }

    if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR) {
    	perror("bind()");
	exit(errno);
    } else {
    	printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);
    }

    /* Ecoute sur le port 5555 */ 
    printf("Listage du port %d...\n", PORT);

    if(listen(sock, NB_MAX_CLIENTS) == SOCKET_ERROR) {
    	perror("listen()");
    	exit(errno);
    }

    return sock;
}

/**
 * Acceptation de la connexion d'un client au serveur
 * @param sock Socket du serveur
 * @return nouvelle socket reliant le client au serveur 
 */
int accept_client(int sock) {
    SOCKADDR_IN csin = {0};
    int csock;
    int sinsize = sizeof(csin);
    
    csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

    if(csock == INVALID_SOCKET) {
        perror("accept()");
        exit(errno);
    }

    return csock;
}

/**
 * Fermeture de connexion d'une socket
 * @param sock Socket a fermer
 */
void close_connection(int sock) {
    printf("Fermeture de la socket %d\n", sock);
    close(sock);
}
