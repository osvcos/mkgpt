#ifndef DEVICE_H
#define DEVICE_H

#include "types.h"

// Values returned by has_partition_scheme
#define PARTSCHEME_IS_NOTHING 0x00000000
#define PARTSCHEME_IS_MBR     0x00000001
#define PARTSCHEME_IS_GPT     0x00000002

struct device {
    // File descriptor returned by open()
    s32 descriptor;
    // Logical sector size
    s32 lsz;
    // Phisical sector size
    s32 psz;
    // Size of the device in bytes
    u64 size;
};

s32 open_device(u8 *devname, struct device *dev);
void close_device(struct device *dev);
s32 has_partition_scheme(struct device *dev);
s32 seek_lba(u64 lba_address, struct device *dev);

#endif // DEVICE_H
