#ifndef MBR_H
#define MBR_H

#include "types.h"

#define MBR_TYPE_PROTECTIVE 0x01
#define MBR_TYPE_LEGACY     0x10

#define MBR_PARTTYPE_GPT_PROTECTIVE 0xEE

typedef struct {
    u8  boot_indicator;
    u8  starting_chs[3];
    u8  os_type;
    u8  ending_chs[3];
    u32 starting_lba;
    u32 size_in_lba;
} __attribute__((packed)) partition_record;

typedef struct {
    u8               boot_code[440];
    u32              disk_id;
    u16              unknown;
    partition_record partitions[4];
    u8               signature[2];
} __attribute__((packed)) master_boot_record;

int create_mbr(struct device *dev, u32 type);

#endif // MBR_H
