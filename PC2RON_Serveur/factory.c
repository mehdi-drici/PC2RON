#include <stdlib.h>
#include <string.h>
#include "factory.h"

/*
*******************************************************************************
 Author: Mehdi Drici

 File: factory.c
 
 Description: Fabrique de trame et de donnees.
              Ce pattern permet de garantir une meilleure independance
              de la couche transport.
*******************************************************************************/

/**
 * Creation d'une trame avec son id
 */
Frame create_frame(uint8_t id) {
    Frame frame_created = malloc(sizeof(struct Frame));
    
    frame_created->pennant = NORMAL_FRAME;
    frame_created->id = id;
    frame_created->size = 0;
    frame_created->data = malloc(sizeof(struct Data));

    return frame_created;
}

/**
 * Creation d'un entier signe sur 8 octets (int8)
 */
Data create_int8(int8_t int8) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = INT8;
    data_created->int8 = int8;

    return data_created;
}

/**
 * Creation d'un entier signe sur 16 octets (int16)
 */
Data create_int16(int16_t int16) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = INT16;
    data_created->int16 = int16;

    return data_created;
}

/**
 * Creation d'un entier signe sur 32 octets (int32)
 */
Data create_int32(int32_t int32) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = INT16;
    data_created->int32 = int32;

    return data_created;
}

/**
 * Creation d'un entier non signe sur 8 octets (uint8)
 */
Data create_uint8(uint8_t uint8) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = UINT8;
    data_created->uint8 = uint8;

    return data_created;
}

/**
 * Creation d'un entier non signe sur 16 octets (uint16)
 */
Data create_uint16(uint16_t uint16) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = UINT16;
    data_created->uint16 = uint16;

    return data_created;
}

/**
 * Creation d'un entier non signe sur 32 octets (uint32)
 */
Data create_uint32(uint32_t uint32) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = UINT32;
    data_created->uint32 = uint32;

    return data_created;
}

/**
 * Creation d'une chaine de caracteres (string)
 */
Data create_string(const char* string) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = STRING;
    data_created->string.size = (uint16_t) strlen(string);
     
    /* Allocation dynamique pour le stockage de la chaine */
    data_created->string.content = calloc(strlen(string), sizeof(char));
    strcpy(data_created->string.content, string);
    
    return data_created;
}

/**
 * Creation d'un flottant de double precision (double)
 */
Data create_double(double dbl) {
    Data data_created = malloc(sizeof(struct Data));
    data_created->type = DOUBLE;
    data_created->dbl = dbl;

    return data_created;
}
