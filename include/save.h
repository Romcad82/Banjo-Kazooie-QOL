#ifndef __SAVE_H__
#define __SAVE_H__

#include "config.h"

#ifdef SAVE_FILE_DATA_SIZE
 #if (SAVE_FILE_DATA_SIZE <= 0x0)
#define ROUNDED_SAVE_DATA_SIZE 0x8
 #elif (SAVE_FILE_DATA_SIZE > 0x1F0)
#define ROUNDED_SAVE_DATA_SIZE 0x1F0
 #else
#define ROUNDED_SAVE_DATA_SIZE (SAVE_FILE_DATA_SIZE + ((8 - (SAVE_FILE_DATA_SIZE % 8)) & ~0x8))
 #endif

 #ifdef NOTE_SAVING
#define ADDITIONAL_DATA_1 0x71
 #endif
 #ifdef JINJO_SAVING
#define ADDITIONAL_DATA_2 0x0A
 #endif

#define SUFFICIENT_SAVE_DATA_SPACE (ROUNDED_SAVE_DATA_SIZE >= (0x70 + ADDITIONAL_DATA_1 + ADDITIONAL_DATA_2))
#endif

typedef struct{
    u8 magic;
    u8 slotIndex;
#ifdef SAVE_FILE_DATA_SIZE
    u8 data[ROUNDED_SAVE_DATA_SIZE];
#else
    u8 data[0x70];
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
