#ifndef MBR_H
#define MBR_H

#define MBR_TYPE_PROTECTIVE 0x01
#define MBR_TYPE_LEGACY     0x10

#define MBR_PARTTYPE_GPT_PROTECTIVE 0xEE

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
    partition_record partitions[4];
    unsigned short signature;
} __attribute__((packed));

int mbr_exists(struct device *dev);
int create_mbr(struct device *dev, int type);

#endif // MBR_H
