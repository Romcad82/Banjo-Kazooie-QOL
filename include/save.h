#ifndef __SAVE_H__
#define __SAVE_H__

#include "config.h"

typedef struct{
    u8 magic;
    u8 slotIndex;
#ifdef EEPROM_16K
    u8 data[0xF0]; // Extra data added for note saving and jinjo saving
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
