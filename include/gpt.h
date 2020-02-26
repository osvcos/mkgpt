#ifndef GPT_H
#define GPT_H

#include "device.h"

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
    unsigned short disk_guid[8];
    unsigned long long partition_entry_lba;
    unsigned int number_of_partition_entries;
    unsigned int size_of_partition_entry;
    unsigned int partition_entry_array_crc32;
} __attribute__((packed)) gpt_header;

int initialize_gpt(struct device *dev);

#endif // GPT_H
