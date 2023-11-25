#include "crc32.h"

#include <stdio.h>
#include <string.h>

int xdxd;
unsigned reverse_crc32(unsigned x)
{
    x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
    x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
    x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
    x = (x << 24) | ((x & 0xFF00) << 8) |
       ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}

unsigned int crc32a(crc32_struct* paquete){
    int j, xd;
    xd = 0;
    uint8_t entro = 0;
    unsigned int byte, crc;
    uint8_t *ptr = &(paquete->cabecera);
    xdxd = strlen((const char* )paquete->datos);
    crc = 0xFFFFFFFF;
    while (ptr != &(paquete->fin)) 
    {
        if (xd == xdxd && !entro)
        {
            ptr = &(paquete->fin)-1;
            entro = 1;
        }
        
        byte = *ptr;
        // Get next byte.
        byte = reverse_crc32(byte);         // 32-bit reversal.
        //printf("%x ", byte);
        for (j = 0; j <= 7; j++)
        {    // Do eight times.
            if ((int)(crc ^ byte) < 0)
                crc = (crc << 1) ^ 0x04C11DB7;
            else crc = crc << 1;
                byte = byte << 1;          // Ready next msg bit.
        }
      ptr++;
      xd++;
    }
   return reverse_crc32(~crc);
}

void crc2string(char* dest, crc32_struct paquete){
    snprintf(dest, 512, "%s,%lx",paquete.datos, paquete.crc32_end_cabecera);
}