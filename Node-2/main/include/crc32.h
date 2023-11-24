#ifndef _MY_CRC32_H
#define _MY_CRC32_H

#include <inttypes.h>
typedef struct 
{
    uint8_t  cabecera;
    uint8_t longitud;
    uint8_t datos[128];
    uint8_t  fin;
    uint32_t crc32_end_cabecera;

} crc32_struct;

unsigned reverse_crc32(unsigned x);

unsigned int crc32a(crc32_struct*);

void crc2string(char* dest, crc32_struct);


#endif