#include "trame.h"
#include "erreur.h"
#include <stdio.h>
#include <stdlib.h>

/*
*******************************************************************************
 Author: Mehdi Drici

 File: frame.c
 
 Description: Gestion d'une trame:
              - ajout de donnees
              - suppression
              - affichage
*******************************************************************************
*/

/**
 * Ajouter une donnee dans une trame 
 * @param frame trame concernee par l'ajout
 * @param data Donnee a ajouter
 */
void add_data(Frame frame, Data data) {
    uint32_t size = frame->size;
    
    /* Premiere allocation memoire pour la premiere donnee */
    if(size == 0) {
        frame->data = (Data*) malloc(sizeof(struct Data));
    }
    
    /* Reallocation dynamique du tableau de donnees a partir du 2eme ajout 
     * Car le tableau est initialise a un seul element
     */
    else {
        frame->data = (Data*) realloc(frame->data, (size+1) * sizeof(struct Data));
    }
    frame->data[size] = data;
    frame->size++;
}

/**
 * Ajouter un ensemble de donnee (tableau) dans une trame 
 * @param frame trame concernee par l'ajout
 * @param data_array Tableau de donnees a ajouter
 */ 
void add_data_array(Frame frame, Data* data_array) {

}


/**
 * Affichage d'une trame
 * @param frame Trame a afficher
 */
void print_frame(Frame frame) {
    int i = 0;

    printf("{ ");

    switch(frame->pennant) {
        case NORMAL_FRAME:
            /* Affichage de l'ID au format hexadecimal  */ 
            printf("%#2.2X", frame->id);

            /* Affichage des données  */ 
            for (i=0; i < frame->size; i++) {
                printf(", ");
                print_data(frame->data[i]);
            }
            break;
            
        case SPECIAL_FRAME:
            printf("%s", STR_END);
            break;
          
        default:
            PRINT_UNKNOWN_PENNANT(frame->pennant);
    }
    
    printf(" }\n");
}

/**
 * Affichage d'une donnee
 * @param data Donnee a afficher
 */
void print_data(Data data) {
    int i = 0;
    
    switch(data->type) {
        case INT8:
            /* { 0x01, n } */
            printf("%s %d", STR_INT8, data->int8);
            break;
            
        case INT16:
            /* { 0x02, n | n} */
            printf("%s %d", STR_INT16, data->int16);
            break;

        case INT32:
            /* { 0x04, n | n | n | n} */
            printf("%s %d", STR_INT32, data->int32);
            break;

        case UINT8:
            /* { 0x11, n } */
            printf("%s %u", STR_UINT8, data->uint8);
            break;

        case UINT16:
            /* { 0x12, n | n} */
            printf("%s %u", STR_UINT16, data->uint16);
            break;

        case UINT32:
            /* { 0x14, n | n | n | n} */
            printf("%s %u", STR_UINT32, data->uint32);
            break;

        case STRING:
            /* { 0x02, s | s | texte } */
            printf("%s \"", STR_STRING);
            
            /* Les octets < 32 et > 127 sont remplaces par \xHH
             * ou HH est la represention hexadecimale de l'octet sur 2 caracteres
             */
            for(i=0; i < data->string.size; i++) {
                if(data->string.content[i] < 32 || data->string.content[i] > 127) {
                    printf("\\x%X", data->string.content[i]);
                } else {
                    printf("%c", data->string.content[i]);
                }
            }
            printf("\"");
            break;

        case DOUBLE:
            /* { 0x02, f | f | f | f | f | f | f | f} */
            printf("%s %f", STR_DOUBLE, data->dbl);
            break;
        
        /* Type de donnee inconnu */
        default:
            PRINT_UNKNOWN_DATA_TYPE(data->type);
    }
}

/**
 * Liberation de l'espace memoire alloue a une trame
 * @param frame Trame a liberer
 */
void free_frame(Frame frame) {
    int i;
    
    /* Liberation de l'espace memoire alloue aux donnees */
    for(i=0; i < frame->size; i++) {
        free(frame->data[i]);
    }
    
    free(frame);
}