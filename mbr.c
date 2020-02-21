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
