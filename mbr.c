#include <string.h>
#include <unistd.h>

#include "device.h"
#include "mbr.h"

int mbr_exists(struct device *dev)
{
    master_boot_record mbr;

    if(seek_lba(0, dev) == -1)
    {
        return -1;
    }
    if(read(dev->descriptor, &mbr, sizeof(master_boot_record)) == -1)
    {
        return -1;
    }
    if(mbr.signature[0] == 0x55 & mbr.signature[1] == 0xAA)
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
    master_boot_record mbr;
    partition_record partitions[4];
    unsigned long long total_sectors;

    if(seek_lba(0, dev) == -1)
        return -1;

    memset(&mbr, 0, sizeof(master_boot_record));
    memset(&partitions, 0, sizeof(partitions));
    
    mbr.signature[0] = 0x55;
    mbr.signature[1] = 0xAA;
    
    if(type == MBR_TYPE_PROTECTIVE)
    {
        partitions[0].boot_indicator = 0x00;

        partitions[0].starting_chs[0] = 0x00;
        partitions[0].starting_chs[1] = 0x02;
        partitions[0].starting_chs[2] = 0x00;

        partitions[0].os_type = MBR_PARTTYPE_GPT_PROTECTIVE;

        // FIXME: Compute the correct CHS address
        partitions[0].ending_chs[0] = 0xFF;
        partitions[0].ending_chs[1] = 0xFF;
        partitions[0].ending_chs[2] = 0xFF;

        partitions[0].starting_lba = 1;

        total_sectors = (dev->size / dev->lsz);
        if(total_sectors > 0xFFFFFFFF)
            partitions[0].size_in_lba = 0xFFFFFFFF;
        else
            partitions[0].size_in_lba = (unsigned int) total_sectors - 1;
    }
    memcpy(mbr.partitions, partitions, sizeof(partitions));

    if(write(dev->descriptor, &mbr, sizeof(master_boot_record)) == -1)
        return -1;

    if(dev->lsz > sizeof(master_boot_record))
    {
        if(write(dev->descriptor, 0, (dev->lsz - sizeof(master_boot_record))))
            return -1;
    }
    return 0;
}
