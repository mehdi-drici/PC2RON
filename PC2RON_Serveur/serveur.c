#include "serveur.h"

int etablir_connexion() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    int valeur_option = 1;

    /* Création de la socket */
    if(sock == INVALID_SOCKET) {
      perror("socket()");
      //exit(errno);
    }

    /* Création de l'interface */
    sin.sin_addr.s_addr = htonl(INADDR_ANY); /* nous sommes un serveur, nous acceptons n'importe quelle adresse */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    // lose the pesky "Address already in use" error message
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &valeur_option, sizeof(int)) == -1) {
    	//logger_errno("setsockopt");
        pthread_exit(NULL);
    }

    if(bind (sock, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR) {
    	perror("bind()");
	//exit(errno);
    } else {
    	//printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);
    }

    if(listen(sock, 5) == SOCKET_ERROR) {
    	perror("listen()");
    	//exit(errno);
    }

    return sock;
}

int accepter_client(int sock) {
	SOCKADDR_IN csin = {0};
	int csock;
	int sinsize = sizeof csin;

	// Connexion du client
	/* Attente pendant laquelle le client se connecte */
	csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

	if(csock == INVALID_SOCKET) {
	    perror("accept()");
	    /*exit(errno);*/
	}

	return csock;
}

void fermer_connexion(int sock) {
        close(sock);
}