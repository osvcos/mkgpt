#ifndef GUID_H
#define GUID_H

typedef struct {
    unsigned int time_low;
    unsigned short time_mid;
    unsigned short time_hi_and_version;
    unsigned char clock_seq_hi_and_reserved;
    unsigned char clock_seq_low;
    unsigned short node1;
    unsigned short node2;
    unsigned short node3;
} __attribute__((packed)) guid_t;

void gen_v4_efi_guid(guid_t *guid);

#endif // GUID_H
