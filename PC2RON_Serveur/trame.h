/*
 * trame.h
 *
 *  Created on: 27 nov. 2011
 *      Author: Mehdi Drici
 */

#ifndef TRAME_H_
#define TRAME_H_

#include <stdint.h>

typedef int SOCKET;

/* Types de donnees de la couche transport*/
typedef enum Datatype {
	INT8   = 0x01,
	INT16  = 0X02,
	INT32  = 0x04,
	UINT8  = 0X11,
	UINT16 = 0x12,
	UINT32 = 0X14,
	STRING = 0x20,
	DOUBLE = 0x30
} Datatype;

/* Representation en chaine de caracteres des types de donnee */
#define STR_INT8   "int8"
#define STR_INT16  "int16"
#define STR_INT32  "int32"
#define STR_UINT8  "uint8"
#define STR_UINT16 "uint16"
#define STR_UINT32 "uint32"
#define STR_STRING "string"
#define STR_DOUBLE "double"
#define STR_END    "END"

/* Types de fanion d'une trame*/
typedef enum Pennant {
    NORMAL_FRAME  = 0xFF,
    SPECIAL_FRAME = 0x00
} Pennant;

/* Structure d'une donnee */
typedef struct Data {
	Datatype type;
        
	union {
            /* Entiers signes */
            int8_t int8;
            int16_t int16;
            int32_t int32;

            /* Entiers non signes */
            uint8_t uint8;
            uint16_t uint16;
            uint32_t uint32;

            /* Chaine de caracteres */
            struct string {
                uint16_t size;
                char* content; 
            } string;

            double dbl;
	};
} *Data;


/* Structure d'une trame */
typedef struct Frame {
    Pennant pennant;
    uint8_t id;
    uint8_t size;
    
    /* Tableau de donnees alloue dynamiquement */
    Data* data;
} *Frame;

/* Affichage d'une trame ou d'une donnee */
void print_frame(Frame frame_to_print);
void print_data(Data data_to_print);

/* Ajout de donnees */
void add_data(Frame frame, Data data_added);
void add_data_array(Frame frame, Data* data_array);

/* Liberation de l'espace mémoire alloué */
void free_frame(Frame frame);

#endif /* TRAME_H_ */
