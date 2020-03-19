#include <fcntl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "device.h"
#include "mbr.h"

s32 open_device(u8 *devname, struct device *dev)
{
    s32 fd = 0;
    s32 lsz = 0;
    s32 psz = 0;
    u64 size = 0;

    fd = open(devname, O_RDWR);
    if(fd < 0)
        return -1;
    if(ioctl(fd, BLKSSZGET, &lsz) == -1)
        lsz = 512;
    if(ioctl(fd, BLKPBSZGET, &psz) == -1)
        psz = 512;
    if(ioctl(fd, BLKGETSIZE64, &size) == -1)
        size = lseek(fd, 0, SEEK_END);

    dev->descriptor = fd;
    dev->lsz = lsz;
    dev->psz = psz;
    dev->size = size;
    return 0;
}

void close_device(struct device *dev)
{
    if(dev->descriptor > 0)
        close(dev->descriptor);
    dev->lsz = 0;
    dev->psz = 0;
    dev->size = 0;
}

s32 has_partition_scheme(struct device *dev)
{
    master_boot_record mbr;
    s32 retval = PARTSCHEME_IS_NOTHING;

    if(seek_lba(0, dev) == -1)
    {
        return -1;
    }
    if(read(dev->descriptor, &mbr, sizeof(master_boot_record)) == -1)
    {
        return -1;
    }
    if(mbr.signature[0] == 0x55 && mbr.signature[1] == 0xAA)
    {
        retval = PARTSCHEME_IS_MBR;
        if(mbr.partitions[0].os_type == 0xEE)
            retval = PARTSCHEME_IS_GPT;
    }
    return retval;
}

s32 seek_lba(u64 lba_address, struct device *dev)
{
    u64 offset = dev->lsz * lba_address;
    return lseek(dev->descriptor, offset, SEEK_SET);
}
