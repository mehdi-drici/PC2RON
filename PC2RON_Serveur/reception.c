#include "reception.h"
#include "erreur.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

/*
*******************************************************************************
 Author: Mehdi Drici

 File: receiver.c
 
 Description: Reception d'une trame ou d'une donnee
              Seule recv_frame est accessible de l'exterieur.
              
 Remarks: En cas de succes, ces fonctions renvoient SUCCES (0), ERROR (-1) sinon 
*******************************************************************************/

/**
 * Reception d'une trame
 * @param sock Socket de la connexion
 * @return Trame recue si succes, NULL sinon
 */
Frame recv_frame(SOCKET sock) {
    Frame frame_recv = malloc(sizeof(struct Frame));
    Data data_recv;
    uint8_t byte_recv;
    ssize_t recv_size = 0;
    int data_counter = 0;
    
    frame_recv->size = 0;
    
    recv_size = recv(sock, &byte_recv, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, recv_size, frame_recv);
    frame_recv->pennant = byte_recv;
    
    /* Traitement suivant le type de fanion recu */
    switch (byte_recv) {
        case NORMAL_FRAME:
            break;

        /* Fin de transmission */ 
        case SPECIAL_FRAME: 
            shutdown(sock, SHUT_RDWR);
            return frame_recv;
        
        /* Fanion de trame inconnu */
        default:
            PRINT_UNKNOWN_PENNANT(byte_recv);
            free_frame(frame_recv);
            return NULL;
    }

    /* Reception de l'id */ 
    recv_size = recv(sock, &byte_recv, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, recv_size, frame_recv);
    frame_recv->id = byte_recv;

    /* Reception du nombre de donnees */ 
    recv_size = recv(sock, &byte_recv, 1, 0);
    EXIT_IF_ERROR_RECV_FRAME(sock, recv_size, frame_recv);
        
    /* Reception des donnees
     * Interruption lors d'une erreur de reception
     */ 
    while (data_counter < byte_recv) {
        data_recv = recv_data(sock);
        if(data_recv == NULL) {
            free_frame(frame_recv);
            return NULL;
        }
        add_data(frame_recv, data_recv);
        data_counter++;
    }
    
    return frame_recv;
}


/**
 * Reception d'une donnee quelconque
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_data(SOCKET sock) {
    uint8_t type;
    ssize_t recv_size;
    
    /* Reception du type de donnee */
    recv_size = recv(sock, &type, 1, 0);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, NULL);

       /*   Ajout du type de data  */ 
       /*  data_recv->type = type;  */ 
    
    switch(type) {
        case INT8:
            return recv_int8(sock);

        case INT16:
            return recv_int16(sock);

        case INT32:
            return recv_int32(sock);

        case UINT8:
            return recv_uint8(sock);

        case UINT16:
            return recv_uint16(sock);

        case UINT32:
            return recv_uint32(sock);

        case STRING:
            return recv_string(sock);

        case DOUBLE:
            return recv_double(sock);

        /* Type de donnee inconnu */
        default:
            PRINT_UNKNOWN_DATA_TYPE(type);
            return NULL;
    }
}

/**
 * Reception d'un entier signe sur 8 octets (int8)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_int8(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    int8_t int8_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */ 
    recv_size = recv(sock, (char*)&int8_recv, sizeof(int8_t), MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);

    data_recv->type = INT8;
    data_recv->int8 = int8_recv;

    return data_recv;
}

/**
 * Reception d'un entier signe sur 16 octets (int16)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_int16(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    int16_t int16_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */  
    recv_size = recv(sock, (char*)&int16_recv, sizeof(int16_t), MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);

    data_recv->type = INT16;
    
    /* Conversion de l'entier en gros boutien */ 
    data_recv->int16 = ntohs(int16_recv);

    return data_recv;
}

/**
 * Reception d'un entier signe sur 32 octets (int32)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_int32(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    int32_t int32_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */ 
    recv_size = recv(sock, (char*)&int32_recv, sizeof(int32_t), MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    
    data_recv->type = INT32;
    
    /* Conversion de l'entier en gros boutien */
    data_recv->int32 = ntohl((uint32_t) int32_recv);

    return data_recv;
}


/**
 * Reception d'un entier non signe sur 8 octets (int8)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_uint8(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    uint8_t uint8_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */ 
    recv_size = recv(sock, (char*)&uint8_recv, 1, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    
    data_recv->type = UINT8;
    data_recv->uint8 = uint8_recv;

    return data_recv;
}

/**
 * Reception d'un entier non signe sur 16 octets (int16)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_uint16(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    uint16_t uint16_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */  
    recv_size = recv(sock, (char*)&uint16_recv, 2, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    
    data_recv->type = UINT16;
    data_recv->uint16 = ntohs(uint16_recv);

    return data_recv;
}

/**
 * Reception d'un entier non signe sur 32 octets (int32)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_uint32(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    uint32_t uint32_recv;
    ssize_t recv_size = 0;

    /* Reception de l'entier */ 
    recv_size = recv(sock, (char*)&uint32_recv, 4, MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    
    data_recv->type = UINT32;
    data_recv->uint32 = ntohl(uint32_recv);

    return data_recv;
}

/**
 * Reception d'une chaine de caracteres (string)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_string(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    unsigned char* string_recv;
    uint16_t size, converted_size;
    ssize_t recv_size = 0;

    /* Reception de la taille de la chaine de caracteres */ 
    recv_size = recv(sock, (char*)&size, sizeof(uint16_t), MSG_WAITALL);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    converted_size = ntohs(size);
    
    /* Reception du contenu de la chaine  */ 
    string_recv = calloc(converted_size, sizeof(char));
    recv_size = recv(sock, string_recv, converted_size, 0);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);
    
    data_recv->type = STRING;
    data_recv->string.size = converted_size;
    data_recv->string.content = string_recv;
    
    return data_recv;
}

/**
 * Reception d'un flottant en double precision (double)
 * @param sock Socket de la connexion
 * @return Donnee recue si succes, NULL sinon
 */
Data recv_double(SOCKET sock) {
    Data data_recv = malloc(sizeof(struct Data));
    double double_recv;
    /*char buffer[8];*/
    ssize_t recv_size = 0;
    /*
    int i = 0;
    double temp = 0, resultat = 0;
     */
       /*   On reçoit une suite de 8 bytes, le premier byte reçu est toujours l'byte de poids fort  */ 
    recv_size = recv(sock, (char*)&double_recv, 8, 0);
    EXIT_IF_ERROR_RECV_DATA(sock, recv_size, data_recv);

       /*   On rassemble les 8 bytes séparé en une seul variable de 8 bytes  */ 
/*
    for (i=1; i < 8; i++)
    {
        temp = buffer[i] << 8*i;
        resultat += temp;
    }
*/
    
       /*   On fini par copier le résultat dans la data  */ 
       /*  data_recv->flottant = resultat;  */ 
    data_recv->type = DOUBLE;
    data_recv->dbl = double_recv;
            
    return data_recv;
}
