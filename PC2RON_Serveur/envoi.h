/* 
 * File:   envoi.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:38
 */

#ifndef ENVOI_H
#define	ENVOI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"

/* Envoi d'une trame de fin de transmission */    
int send_EOT(SOCKET sock);

/* Envoi d'une trame */
int send_frame(SOCKET sock, Frame frame);

/* Envoi d'une donnee quelconque */
int send_data(SOCKET sock, Data data);

/* Envpo d'une donnee specifique */
int send_int8(SOCKET sock, Data data);
int send_int16(SOCKET sock, Data data);
int send_int32(SOCKET sock, Data data);
int send_uint8(SOCKET sock, Data data);
int send_uint16(SOCKET sock, Data data);
int send_uint32(SOCKET sock, Data data);
int send_string(SOCKET sock, Data data);
int send_double(SOCKET sock, Data data);

#ifdef	__cplusplus
}
#endif

#endif	/* ENVOI_H */

