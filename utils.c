#include "utils.h"

unsigned long get_crc32(const Bytef* data, unsigned int len)
{
    unsigned long crc = crc32(0L, Z_NULL, 0);
    for(int i = 0; i < len; i++)
        crc = crc32(crc, data + i, 1);
    return crc;
}
