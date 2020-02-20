#include <fcntl.h>
#include <linux/fs.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "device.h"

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
    if(ioctl(fd, BLKBSZGET, &psz) == -1)
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
    dev = NULL;
}
