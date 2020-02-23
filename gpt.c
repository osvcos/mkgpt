#include <string.h>
#include <unistd.h>
#include <zlib.h>

#include "device.h"
#include "mbr.h"
#include "gpt.h"

int initialize_gpt(struct device *dev)
{
    gpt_header gpt;

    memset(&gpt, 0, sizeof(gpt_header));
    if(create_mbr(dev, MBR_TYPE_PROTECTIVE) == -1)
        return -1;
    if(seek_lba(1, dev) == -1)
        return -1;

    memcpy(gpt.signature, "EFI PART", sizeof(gpt.signature));

    gpt.revision[0] = 0x00;
    gpt.revision[1] = 0x00;
    gpt.revision[2] = 0x01;
    gpt.revision[3] = 0x00;

    gpt.header_size = sizeof(gpt_header);

    gpt.my_lba = 1;
    gpt.alternate_lba = (dev->size / dev->lsz);
    gpt.first_usable_lba = ((16385 / dev->lsz) + 2);

    gpt.header_crc32 = crc32(0L, Z_NULL, 0);
    for(int i = 0; i < sizeof(gpt_header); i++)
        gpt.header_crc32 = crc32(gpt.header_crc32, (unsigned char*) &gpt + i, 1);

    if((write(dev->descriptor, &gpt, sizeof(gpt_header)) == -1))
        return -1;
    return 0;
}
