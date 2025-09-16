#ifndef __SAVE_H__
#define __SAVE_H__

#include "config.h"

typedef struct{
    u8 magic;
    u8 slotIndex;
#ifndef SAVE_FILE_DATA_SIZE
    u8 data[0x70];
#elif (0x8 <= SAVE_FILE_DATA_SIZE) && (SAVE_FILE_DATA_SIZE <= 0x1F0)
    u8 data[SAVE_FILE_DATA_SIZE - (SAVE_FILE_DATA_SIZE % 8)];
#elif (SAVE_FILE_DATA_SIZE < 0x8)
    u8 data[0x8];
#elif (0x1F0 < SAVE_FILE_DATA_SIZE)
    u8 data[0x1F0];
#endif
    u8 padding[0x2];
    u32 checksum;
}SaveData;

typedef struct {
    u32 snsItems;
    u8 padding[0x18];
    u32 checksum;
}GlobalData;

#endif
