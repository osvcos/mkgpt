#include "endian.h"

unsigned short swap_u16(unsigned short value)
{
    unsigned short result = 0;
    result |= ((value & 0xFF00) >> 8);
    result |= ((value & 0x00FF) << 8);
    return result;
}
