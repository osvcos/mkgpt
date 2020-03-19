#ifndef GUID_H
#define GUID_H

#include "types.h"

typedef struct {
    u32 time_low;
    u16 time_mid;
    u16 time_hi_and_version;
    u8  clock_seq_hi_and_reserved;
    u8  clock_seq_low;
    u16 node1;
    u16 node2;
    u16 node3;
} __attribute__((packed)) guid_t;

void gen_v4_efi_guid(guid_t *guid);

#endif // GUID_H
