#include <string.h>
#include <unistd.h>

#include "device.h"
#include "mbr.h"

int mbr_exists(struct device *dev)
{
    struct master_boot_record mbr;

    if(seek_lba(0, dev) == -1)
    {
        return -1;
    }
    if(read(dev->descriptor, &mbr, sizeof(struct master_boot_record)) == -1)
    {
        return -1;
    }
    if(mbr.signature == 0xAA55)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int create_mbr(struct device *dev, int type)
{
    struct master_boot_record mbr;
    partition_record partitions[4];

    if(seek_lba(0, dev) == -1)
        return -1;

    memset(&mbr, 0, sizeof(struct master_boot_record));
    memset(&partitions, 0, sizeof(partitions));

    if(write(dev->descriptor, 0, dev->lsz) == -1)
        return -1;

    if(type == MBR_TYPE_PROTECTIVE)
        mbr.disk_signature = 0;
    
    mbr.signature == 0xAA55;
    
    if(type == MBR_TYPE_PROTECTIVE)
    {
        partitions[0].boot_indicator = 0x00;
        memset(partitions[0].starting_chs, 0x000200, sizeof(partitions[0].starting_chs));
        partitions[0].os_type = MBR_PARTTYPE_GPT_PROTECTIVE;
        // FIXME: Compute the correct CHS address
        memset(partitions[0].ending_chs, 0xFFFFFFFF, sizeof(partitions[0].ending_chs));
        partitions[0].starting_lba = 1;
        partitions[0].size_in_lba = ((dev->size / dev->lsz) - 1);
    }
    memcpy(mbr.partitions, partitions, sizeof(partitions));

    if(write(dev->descriptor, &mbr, sizeof(struct master_boot_record)) == -1)
        return -1;
    if(dev->lsz > sizeof(struct master_boot_record))
    {
        if(write(dev->descriptor, 0, (dev->lsz - sizeof(struct master_boot_record))))
            return -1;
    }
    return 0;
}
