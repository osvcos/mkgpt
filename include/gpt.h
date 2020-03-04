#ifndef GPT_H
#define GPT_H

#include <zlib.h>

#include "device.h"
#include "guid.h"

typedef struct {
    unsigned short partition_type_guid[8];
    unsigned short partition_guid[8];
    unsigned long long starting_lba;
    unsigned long long ending_lba;
    unsigned long long attributes;
    unsigned char partition_name[72];
} __attribute__((packed)) gpt_partition_entry;

typedef struct {
    unsigned char signature[8];
    unsigned int revision;
    unsigned int header_size;
    unsigned int header_crc32;
    unsigned int reserved;
    unsigned long long my_lba;
    unsigned long long alternate_lba;
    unsigned long long first_usable_lba;
    unsigned long long last_usable_lba;
    guid_t disk_guid;
    unsigned long long partition_entry_lba;
    unsigned int number_of_partition_entries;
    unsigned int size_of_partition_entry;
    unsigned int partition_entry_array_crc32;
} __attribute__((packed)) gpt_header;

static unsigned long get_crc32(const Bytef* data, unsigned int len)
{
    unsigned long crc = crc32(0L, Z_NULL, 0);
    for(int i = 0; i < len; i++)
        crc = crc32(crc, data + i, 1);
    return crc;
}

int initialize_gpt(struct device *dev);

#endif // GPT_H
