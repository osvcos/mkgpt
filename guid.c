#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "endian.h"
#include "guid.h"

void gen_v4_efi_guid(guid_t *guid)
{
    srand(time(NULL));
    memset(guid, 0, sizeof(guid_t));
    guid->time_low = rand() % RAND_MAX;
    guid->time_mid = rand() % RAND_MAX;
    guid->time_hi_and_version = rand() % RAND_MAX;
    guid->time_hi_and_version &= 0x0FFF;
    guid->time_hi_and_version |= 0x4000;
    guid->clock_seq_hi_and_reserved = rand() % RAND_MAX;
    guid->clock_seq_hi_and_reserved &= 0x3F;
    guid->clock_seq_hi_and_reserved |= 0x80;
    guid->node1 = rand() % RAND_MAX;
    guid->node1 = swap_u16(guid->node1);
    guid->node2 = rand() % RAND_MAX;
    guid->node2 = swap_u16(guid->node2);
    guid->node3 = rand() % RAND_MAX;
    guid->node3 = swap_u16(guid->node3);
}
