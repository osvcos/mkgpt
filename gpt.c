#include <string.h>
#include <unistd.h>

#include "device.h"
#include "mbr.h"
#include "gpt.h"
#include "guid.h"

int initialize_gpt(struct device *dev)
{
    gpt_header primary_gpt;
    gpt_header backup_gpt;
    gpt_partition_entry parts[128];
    guid_t guid;
    unsigned long long first_usable_lba;
    unsigned long long last_usable_lba;
    unsigned long long last_lba;

    if(create_mbr(dev, MBR_TYPE_PROTECTIVE) == -1)
        return -1;

    memset(&primary_gpt, 0, sizeof(gpt_header));
    memset(&backup_gpt, 0, sizeof(gpt_header));
    memset(parts, 0, sizeof(parts));

    memcpy(primary_gpt.signature, "EFI PART", sizeof(primary_gpt.signature));
    memcpy(backup_gpt.signature, "EFI PART", sizeof(primary_gpt.signature));

    primary_gpt.revision = 0x00010000;
    backup_gpt.revision = 0x00010000;

    primary_gpt.header_size = sizeof(gpt_header);
    backup_gpt.header_size = sizeof(gpt_header);

    last_lba = (dev->size / dev->lsz) - 1;

    primary_gpt.my_lba = 1;
    backup_gpt.my_lba = last_lba;

    primary_gpt.alternate_lba = last_lba;
    backup_gpt.alternate_lba = 1;

    first_usable_lba = ((sizeof(gpt_partition_entry) / (dev->lsz / sizeof(gpt_partition_entry))) + 2);
    last_usable_lba = (last_lba - 1 - (first_usable_lba - 2));

    primary_gpt.first_usable_lba = first_usable_lba;
    backup_gpt.first_usable_lba = first_usable_lba;

    primary_gpt.last_usable_lba = last_usable_lba;
    backup_gpt.last_usable_lba = last_usable_lba;

    gen_v4_efi_guid(&guid);
    primary_gpt.disk_guid = guid;
    backup_gpt.disk_guid = guid;

    primary_gpt.partition_entry_lba = 2;
    backup_gpt.partition_entry_lba = last_usable_lba + 1;

    primary_gpt.number_of_partition_entries = 128;
    backup_gpt.number_of_partition_entries = 128;

    primary_gpt.size_of_partition_entry = sizeof(gpt_partition_entry);
    backup_gpt.size_of_partition_entry = sizeof(gpt_partition_entry);

    primary_gpt.partition_entry_array_crc32 = get_crc32((const Bytef*) parts, sizeof(parts));
    backup_gpt.partition_entry_array_crc32 = get_crc32((const Bytef*) parts, sizeof(parts));

    primary_gpt.header_crc32 = get_crc32((const Bytef*) &primary_gpt, sizeof(gpt_header));
    backup_gpt.header_crc32 = get_crc32((const Bytef*) &backup_gpt, sizeof(gpt_header));

    if(seek_lba(1, dev) == -1)
        return -1;
    if(write(dev->descriptor, &primary_gpt, sizeof(gpt_header)) == -1)
        return -1;
    if(seek_lba(2, dev) == -1)
        return -1;
    if(write(dev->descriptor, parts, sizeof(parts)) == -1)
        return -1;
    if(seek_lba((last_usable_lba + 1), dev) == -1)
        return -1;
    if(write(dev->descriptor, parts, sizeof(parts)) == -1)
        return -1;
    if(seek_lba(last_lba, dev) == -1)
        return -1;
    if(write(dev->descriptor, &backup_gpt, sizeof(gpt_header)) == -1)
        return -1;
    return 0;
}
