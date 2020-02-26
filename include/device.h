#ifndef DEVICE_H
#define DEVICE_H

#define PARTSCHEME_IS_NOTHING 0x00000000
#define PARTSCHEME_IS_MBR     0x00000001
#define PARTSCHEME_IS_GPT     0x00000002

struct device {
    // File descriptor returned by open()
    int descriptor;
    // Logical sector size
    int lsz;
    // Phisical sector size
    int psz;
    // Size of the device in bytes
    unsigned long long size;
};

int open_device(char *devname, struct device *dev);
void close_device(struct device *dev);
int has_partition_scheme(struct device *dev);
int seek_lba(unsigned long long lba_address, struct device *dev);

#endif // DEVICE_H
