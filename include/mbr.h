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

typedef struct {
    unsigned char boot_code[440];
    unsigned int disk_id;
    unsigned short unknown;
    partition_record partitions[4];
    unsigned char signature[2];
} __attribute__((packed)) master_boot_record;

int create_mbr(struct device *dev, int type);

#endif // MBR_H
