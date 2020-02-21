#ifndef MBR_H
#define MBR_H

typedef struct {
    unsigned char boot_indicator;
    unsigned char starting_chs[3];
    unsigned char os_type;
    unsigned char ending_chs[3];
    unsigned int starting_lba;
    unsigned int size_in_lba;
    
} __attribute__((packed)) partition_record;

struct master_boot_record {
    char boot_code[440];
    unsigned int disk_signature;
    unsigned short unknown;
    partition_record parttitions[4];
    unsigned short signature;
} __attribute__((packed));

int mbr_exists(struct device *dev);

#endif // MBR_H
