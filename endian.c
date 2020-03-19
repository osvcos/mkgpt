#include "endian.h"

u16 swap_u16(u16 value)
{
    u16 result = 0;
    result |= ((value & 0xFF00) >> 8);
    result |= ((value & 0x00FF) << 8);
    return result;
}
