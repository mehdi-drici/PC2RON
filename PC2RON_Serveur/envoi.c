#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
 #include <netinet/in.h>
#include "envoi.h"
#include "erreur.h"

/*
*******************************************************************************
 Author: Mehdi Drici

 File: sender.c
 
 Description: Envoi d'une trame ou d'une donnee
              Seules send_EOT et send_frame sont accessibles de l'exterieur.
              
 Remarks:    En cas de succes, elles renvoient SUCCES (0), ERROR (-1) sinon 
*******************************************************************************
*/


/**
 * Envoi d'une trame de fin de transmission
 * @param sock Socket de la connexion
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_EOT(SOCKET sock) {
    ssize_t sent_size = 0;
    Pennant frame = SPECIAL_FRAME;
    
    sent_size = send(sock, (char*)&(frame), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);
    
    return SUCCESS;
}

/**
 * Envoi d'une trame
 * @param sock Socket de la connexion
 * @param frame Trame a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_frame(SOCKET sock, Frame frame) {    
    ssize_t sent_size = 0;
    int data_counter = 0;
    
    /* Envoi de l'entete */
    sent_size = send(sock, (char*)&(frame->pennant), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);
    
    sent_size = send(sock, (char*)&(frame->id), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);
    
    sent_size = send(sock, (char*)&(frame->size), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);
    
    /* Envoi des donnees
     * Interruption lors d'une erreur d'envoi
     */ 
    while (data_counter < frame->size) {
        if(send_data(sock, frame->data[data_counter]) == ERROR) {
            return ERROR;
        }
        data_counter++;
    }
    
    return SUCCESS;
}

/**
 * Envoi d'une donnee quelconque
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_data(SOCKET sock, Data data) {
    switch(data->type) {
        case INT8:
            return send_int8(sock, data);

        case INT16:
            return send_int16(sock, data);

        case INT32:
            return send_int32(sock, data);

        case UINT8:
            return send_uint8(sock, data);

        case UINT16:
            return send_uint16(sock, data);

        case UINT32:
            return send_uint32(sock, data);

        case STRING:
            return send_string(sock, data);

        case DOUBLE:
            return send_double(sock, data);
        
        /* Le type de donnee est inconnu */
        default:
            return ERROR;
    }
}

/**
 * Envoi d'un entier signe de 8 octets (int8)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_int8(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Envoi du type donnee */ 
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, &(data->int8), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}

/**
 * Envoi d'un entier signe sur 16 octets (int16)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_int16(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Conversion de l'entier en gros boutien */ 
    int16_t data_converted = htons(data->int16);

    /* Envoi du type de donnee */ 
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, (char*)&data_converted, sizeof(int16_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}


/**
 * Envoi d'un entier signe sur 32 octets (int32)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_int32(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Conversion de l'entier en gros boutien */     
    long int32_converted = htonl((uint32_t) data->int32);

    /* Envoi du type de donnee */ 
    sent_size = send(sock, (char*)data->type, sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, (char*)&int32_converted, sizeof(int32_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}

/**
 * Envoi d'un entier non signe sur 8 octets (uint8)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_uint8(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Envoi du type de donnee */ 
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, &(data->uint8), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}

/**
 * Envoi d'un entier non signe sur 16 octets (uint16)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_uint16(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Conversion de l'entier en gros boutien */ 
    uint16_t uint16_converted = htons(data->uint16);

    /* Envoi du type de donnee */  
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, (char*)&uint16_converted, sizeof(uint16_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}

/**
 * Envoi d'un entier non signe sur 32 octets (uint32)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_uint32(SOCKET sock, Data data) {
    ssize_t sent_size = 0;

    /* Conversion de l'entier en gros boutien */
    uint32_t uint32_converted = htonl(data->uint32);

    /* Envoi du type de donnee */  
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de l'entier */ 
    sent_size = send(sock, (char*)&uint32_converted, sizeof(int32_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    return SUCCESS;
}

/**
 * Envoi d'une chaine de caracteres (string)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 */
int send_string(SOCKET sock, Data data) {
    ssize_t sent_size = 0;
    
    /* Conversion de l'entier en gros boutien */ 
    uint16_t uint16_converted = htons(data->string.size);
    
    /* Envoi du type de donnee */   
    sent_size = send(sock, (char*)&(data->type), sizeof(uint8_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

    /* Envoi de la taille de la chaine */ 
    sent_size = send(sock, (char*)&uint16_converted, sizeof(uint16_t), 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);

       /*   Envoi de la chaine  */ 
    sent_size = send(sock, data->string.content, data->string.size, 0);
    EXIT_IF_ERROR_SEND(sock, sent_size);
        
    return SUCCESS;
}

/**
 * Envoi d'un flottant en double precision (double)
 * Cette fonction a une portee locale au fichier
 * @param sock Socket de la connexion
 * @param data Donnee a envoyer
 * @return SUCCESS(0) ou ERROR(-1)
 * @TODO Conversion Double en Octets
 */
int send_double(SOCKET sock, Data flottantEnvoye) {
    int nbOctetsEnvoyes = 0;
    char donnees[8];

       /*   Envoi de l'entête  */ 
    nbOctetsEnvoyes = send(sock, (char*)&(flottantEnvoye->type), 1, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);

       /*   Envoi du flottant  */ 
    /*
    @todo codage du flottant
    donnees[0] = (flottantEnvoye->flottant >> 56) & 0xFF;
    donnees[1] = (flottantEnvoye->flottant >> 48) & 0xFF;
    donnees[2] = (flottantEnvoye->flottant >> 40) & 0xFF;
    donnees[3] = (flottantEnvoye->flottant >> 32) & 0xFF;
    donnees[4] = (flottantEnvoye->flottant >> 24) & 0xFF;
    donnees[5] = (flottantEnvoye->flottant >> 16) & 0xFF;
    donnees[6] = (flottantEnvoye->flottant >> 8) & 0xFF;
    donnees[7] = (flottantEnvoye->flottant >> 0) & 0xFF;
     */
    
    nbOctetsEnvoyes = send(sock, donnees, 8, 0);
    EXIT_IF_ERROR_SEND(sock, nbOctetsEnvoyes);
    
    return SUCCESS;
}
