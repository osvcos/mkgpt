#ifndef GPT_H
#define GPT_H

#include "device.h"
#include "guid.h"
#include "types.h"

typedef struct {
    guid_t partition_type_guid;
    guid_t partition_guid;
    u64    starting_lba;
    u64    ending_lba;
    u64    attributes;
    u8     partition_name[72];
} __attribute__((packed)) gpt_partition_entry;

typedef struct {
    u64    signature;
    u32    revision;
    u32    header_size;
    u32    header_crc32;
    u32    reserved;
    u64    my_lba;
    u64    alternate_lba;
    u64    first_usable_lba;
    u64    last_usable_lba;
    guid_t disk_guid;
    u64    partition_entry_lba;
    u32    number_of_partition_entries;
    u32    size_of_partition_entry;
    u32    partition_entry_array_crc32;
} __attribute__((packed)) gpt_header;

s32 initialize_gpt(struct device *dev);

#endif // GPT_H
