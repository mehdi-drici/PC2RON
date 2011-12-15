/* 
 * File:   reception.h
 * Author: mehdi
 *
 * Created on 7 décembre 2011, 23:38
 */

#ifndef RECEPTION_H
#define	RECEPTION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "trame.h"
    
Frame recv_frame(SOCKET sock);
Data recv_data(SOCKET sock);
Data recv_int8(SOCKET sock);
Data recv_int16(SOCKET sock);
Data recv_int32(SOCKET sock);
Data recv_uint8(SOCKET sock);
Data recv_uint16(SOCKET sock);
Data recv_uint32(SOCKET sock);
Data recv_string(SOCKET sock);
Data recv_double(SOCKET sock);

#ifdef	__cplusplus
}
#endif

#endif	/* RECEPTION_H */

