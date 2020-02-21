#ifndef MBR_H
#define MBR_H

struct master_boot_record {
    char boot_code[440];
    unsigned int disk_signature;
    unsigned short unknown;
    unsigned long long parttitions[8];
    unsigned short signature;
} __attribute__((packed));

int mbr_exists(struct device *dev);

#endif // MBR_H
