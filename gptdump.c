#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "device.h"
#include "endian.h"
#include "gpt.h"

void print_gpt_info(gpt_header *gpt)
{
    printf("Signature: %s\n", gpt->signature);
    printf("Revision: 0x%.4x\n", gpt->revision);
    printf("Header size: %lu\n", gpt->header_size);
    printf("Header CRC32 Checksum: %lu\n", gpt->header_crc32);
    printf("My LBA: %llu\n", gpt->my_lba);
    printf("Alternate LBA: %llu\n", gpt->alternate_lba);
    printf("First usable LBA: %llu\n", gpt->first_usable_lba);
    printf("Last usable LBA: %llu\n", gpt->last_usable_lba);
    printf("Disk GUID: %.8X-%.4X-%.4X-%.2X%.2X-%X%X%X\n", gpt->disk_guid.time_low, gpt->disk_guid.time_mid, gpt->disk_guid.time_hi_and_version, gpt->disk_guid.clock_seq_hi_and_reserved, gpt->disk_guid.clock_seq_low, swap_u16(gpt->disk_guid.node1), swap_u16(gpt->disk_guid.node2), swap_u16(gpt->disk_guid.node3));
    printf("Partition entry LBA: %llu\n", gpt->partition_entry_lba);
    printf("Number of partition entries: %lu\n", gpt->number_of_partition_entries);
    printf("Size of partition entry: %lu\n", gpt->size_of_partition_entry);
    printf("CRC32 Checksum of partition entry array: %lu\n", gpt->partition_entry_array_crc32);
}

void usage()
{
    printf("usage: gptdump device\n");
}

int main(int argc, char *argv[])
{
    struct device dev;
    gpt_header primary_gpt;
    gpt_header backup_gpt;
    unsigned long long last_lba;

    if(argc < 2)
    {
        usage();
        return 1;
    }

    if(open_device(argv[1], &dev) == -1)
    {
        printf("Could not open device(%d): %s\n", errno, strerror(errno));
        return -1;
    }

    last_lba = (dev.size / dev.lsz) - 1;

    printf("Total LBAs: %llu\n\n", last_lba + 1);
    if(seek_lba(1, &dev) == -1)
    {
        printf("Error seeking to lba 1(%d): %s\n", errno, strerror(errno));
        close_device(&dev);
        return -1;
    }
    if(read(dev.descriptor, &primary_gpt, sizeof(gpt_header)) == -1)
    {
        printf("Could not read primary GPT(%d): %s\n", errno, strerror(errno));
        close_device(&dev);
        return -1;
    }
    if(seek_lba(last_lba, &dev) == -1)
    {
        printf("Error seeking to LBA %llu(%d): %s\n", last_lba, errno, strerror(errno));
        close_device(&dev);
        return -1;
    }
    if(read(dev.descriptor, &backup_gpt, sizeof(gpt_header)) == -1)
    {
        printf("Could not read backup GPT(%d): %s\n", errno, strerror(errno));
        close_device(&dev);
        return -1;
    }
    printf("Primary GPT\n");
    printf("===========\n");
    print_gpt_info(&primary_gpt);
    printf("\n\nBackup GPT\n");
    printf("==========\n");
    print_gpt_info(&backup_gpt);
    close_device(&dev);
    return 0;
}
