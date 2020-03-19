#ifndef GPT_H
#define GPT_H

#include "device.h"
#include "guid.h"

typedef struct {
    guid_t partition_type_guid;
    guid_t partition_guid;
    unsigned long long starting_lba;
    unsigned long long ending_lba;
    unsigned long long attributes;
    unsigned char partition_name[72];
} __attribute__((packed)) gpt_partition_entry;

typedef struct {
    unsigned long long signature;
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

int initialize_gpt(struct device *dev);

#endif // GPT_H
