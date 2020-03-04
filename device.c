#include <fcntl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "device.h"
#include "mbr.h"

int open_device(char *devname, struct device *dev)
{
    int fd = 0;
    int lsz = 0;
    int psz = 0;
    unsigned long long size = 0;

    fd = open(devname, O_RDWR);
    if(fd < 0)
        return -1;
    if(ioctl(fd, BLKSSZGET, &lsz) == -1)
        return -1;
    if(ioctl(fd, BLKPBSZGET, &psz) == -1)
        return -1;
    if(ioctl(fd, BLKGETSIZE64, &size) == -1)
        return -1;

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

int has_partition_scheme(struct device *dev)
{
    master_boot_record mbr;
    int retval = PARTSCHEME_IS_NOTHING;

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

int seek_lba(unsigned long long lba_address, struct device *dev)
{
    unsigned long long offset = dev->lsz * lba_address;
    return lseek(dev->descriptor, offset, SEEK_SET);
}
