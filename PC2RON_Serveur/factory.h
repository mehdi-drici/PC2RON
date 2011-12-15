/* 
 * File:   factory.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:39
 */

#ifndef FACTORY_H
#define	FACTORY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"

/* Création d'une trame */
Frame create_frame(uint8_t id);

/* Creation d'une donnee specifique */
Data create_int8(int8_t int8);
Data create_int16(int16_t int16);
Data create_int32(int32_t int32);
Data create_uint8(uint8_t uint8);
Data create_uint16(uint16_t uint16);
Data create_uint32(uint32_t uint32);
Data create_string(const char* string);
Data create_double(double dbl);

#ifdef	__cplusplus
}
#endif

#endif	/* FACTORY_H */

