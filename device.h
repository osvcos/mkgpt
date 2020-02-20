#ifndef DEVICE_H
#define DEVICE_H

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

#endif // DEVICE_H
