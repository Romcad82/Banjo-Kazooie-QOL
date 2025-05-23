#include <ultra64.h>
#include "core1/core1.h"
#include "functions.h"
#include "variables.h"

#include "save.h"

#include "config.h"


typedef struct {
    s16 unk0; // enum volatile_flags_e
    s16 unk2; // enum file_progress_e
}Struct_B5040;

void savedata_clear(u8 *savedata);
s32 savedata_verify(s32 arg0, SaveData *savedata);

/* .data */
Struct_B5040 D_80370A20[] = {
    {VOLATILE_FLAG_66_SANDCASTLE_OPEN_DOOR_TWO, FILEPROG_FF_SANDCASTLE_OPEN_DOOR_TWO},
    {VOLATILE_FLAG_67_SANDCASTLE_OPEN_DOOR_THREE, FILEPROG_100_SANDCASTLE_OPEN_DOOR_THREE},
    {VOLATILE_FLAG_68_SANDCASTLE_OPEN_DOOR_FOUR, FILEPROG_101_SANDCASTLE_OPEN_DOOR_FOUR},
    {VOLATILE_FLAG_69_SANDCASTLE_OPEN_DOOR_FIVE, FILEPROG_102_SANDCASTLE_OPEN_DOOR_FIVE},
    {VOLATILE_FLAG_6A_SANDCASTLE_OPEN_DOOR_SIX, FILEPROG_103_SANDCASTLE_OPEN_DOOR_SIX},
    {VOLATILE_FLAG_6B_SANDCASTLE_OPEN_DOOR_SEVEN, FILEPROG_104_SANDCASTLE_OPEN_DOOR_SEVEN},
    {VOLATILE_FLAG_6C_SANDCASTLE_PUZZLE_COMPLETE_CC, FILEPROG_105_SANDCASTLE_PUZZLE_COMPLETE_CC},
    {VOLATILE_FLAG_6D_SANDCASTLE_PUZZLE_COMPLETE_BGS, FILEPROG_106_SANDCASTLE_PUZZLE_COMPLETE_BGS},
    {VOLATILE_FLAG_6E_SANDCASTLE_PUZZLE_COMPLETE_FP, FILEPROG_107_SANDCASTLE_PUZZLE_COMPLETE_FP},
    {VOLATILE_FLAG_6F_SANDCASTLE_PUZZLE_COMPLETE_GV, FILEPROG_108_SANDCASTLE_PUZZLE_COMPLETE_GV},
    {VOLATILE_FLAG_70_SANDCASTLE_PUZZLE_COMPLETE_MMM, FILEPROG_109_SANDCASTLE_PUZZLE_COMPLETE_MMM},
    {VOLATILE_FLAG_71_SANDCASTLE_PUZZLE_COMPLETE_RBB, FILEPROG_10A_SANDCASTLE_PUZZLE_COMPLETE_RBB},
    {VOLATILE_FLAG_72_SANDCASTLE_PUZZLE_COMPLETE_CCC, FILEPROG_10B_SANDCASTLE_PUZZLE_COMPLETE_CCC},
    {VOLATILE_FLAG_7D_SANDCASTLE_RAISE_PIPES_TO_CC, FILEPROG_10C_SANDCASTLE_RAISE_PIPES_TO_CC},
    {VOLATILE_FLAG_7E_SANDCASTLE_RAISE_PIPE_TO_BRENTILDA, FILEPROG_10D_SANDCASTLE_RAISE_PIPE_TO_BRENTILDA},
    {VOLATILE_FLAG_7F_SANDCASTLE_OPEN_CC, FILEPROG_10E_SANDCASTLE_OPEN_CC},
    {VOLATILE_FLAG_80_SANDCASTLE_REMOVE_GRILL_NEAR_BGS_JIGGY, FILEPROG_10F_SANDCASTLE_REMOVE_GRILL_NEAR_BGS_JIGGY},
    {VOLATILE_FLAG_81_SANDCASTLE_CCC_JIGGY_PODIUM, FILEPROG_110_SANDCASTLE_CCC_JIGGY_PODIUM},
    {VOLATILE_FLAG_82_SANDCASTLE_REMOVE_GRILL_AND_HAT_FROM_STATUE, FILEPROG_111_SANDCASTLE_REMOVE_GRILL_AND_HAT_FROM_STATUE},
    {VOLATILE_FLAG_83_SANDCASTLE_REMOVE_ICE, FILEPROG_112_SANDCASTLE_REMOVE_ICE},
    {VOLATILE_FLAG_84_SANDCASTLE_OPEN_BGS, FILEPROG_113_SANDCASTLE_OPEN_BGS},
    {VOLATILE_FLAG_85_SANDCASTLE_REMOVE_BREAKABLE_WALLS, FILEPROG_114_SANDCASTLE_REMOVE_BREAKABLE_WALLS},
    {VOLATILE_FLAG_86_SANDCASTLE_SHOCKSPRING_JUMP_UNLOCKED, FILEPROG_115_SANDCASTLE_SHOCKSPRING_JUMP_UNLOCKED},
    {VOLATILE_FLAG_87_SANDCASTLE_OPEN_GV, FILEPROG_116_SANDCASTLE_OPEN_GV},
    {VOLATILE_FLAG_88_SANDCASTLE_REMOVE_WEBS, FILEPROG_117_SANDCASTLE_REMOVE_WEBS},
    {VOLATILE_FLAG_89_SANDCASTLE_REMOVE_GLASS_EYE, FILEPROG_118_SANDCASTLE_REMOVE_GLASS_EYE},
    {VOLATILE_FLAG_8A_SANDCASTLE_FLIGHT_UNLOCKED, FILEPROG_119_SANDCASTLE_FLIGHT_UNLOCKED},
    {VOLATILE_FLAG_8B_SANDCASTLE_OPEN_FP, FILEPROG_11A_SANDCASTLE_OPEN_FP},
    {VOLATILE_FLAG_8C_SANDCASTLE_OPEN_MMM, FILEPROG_11B_SANDCASTLE_OPEN_MMM},
    {VOLATILE_FLAG_8D_SANDCASTLE_REMOVE_CRYPT_GATE, FILEPROG_11C_SANDCASTLE_REMOVE_CRYPT_GATE},
    {VOLATILE_FLAG_8E_SANDCASTLE_REMOVE_CRYPT_COFFIN_LID, FILEPROG_11D_SANDCASTLE_REMOVE_CRYPT_COFFIN_LID},
    {VOLATILE_FLAG_8F_SANDCASTLE_REMOVE_GRATE_NEAR_WATER_SWITCH, FILEPROG_11E_SANDCASTLE_REMOVE_GRATE_NEAR_WATER_SWITCH},
    {VOLATILE_FLAG_90_SANDCASTLE_OPEN_RBB, FILEPROG_11F_SANDCASTLE_OPEN_RBB},
    {VOLATILE_FLAG_91_SANDCASTLE_REMOVE_GRILL_NEAR_RBB_JIGGY, FILEPROG_120_SANDCASTLE_REMOVE_GRILL_NEAR_RBB_JIGGY},
    {VOLATILE_FLAG_92_SANDCASTLE_REMOVE_TUNNEL_GRILL_NEAR_RBB_JIGGY, FILEPROG_121_SANDCASTLE_REMOVE_TUNNEL_GRILL_NEAR_RBB_JIGGY},
    {VOLATILE_FLAG_93_SANDCASTLE_OPEN_CCW, FILEPROG_122_SANDCASTLE_OPEN_CCW},
#ifdef ADDITIONAL_CHEATS
    {VOLATILE_FLAG_79_SANDCASTLE_UNLOCK_ALL, FILEPROG_124_SANDCASTLE_UNLOCK_ALL},
    {VOLATILE_FLAG_7A_SANDCASTLE_RAISE_WATER_LEVEL, FILEPROG_125_SANDCASTLE_RAISE_WATER_LEVEL},
    {VOLATILE_FLAG_7B_SANDCASTLE_OPEN_DOOR_EIGHT, FILEPROG_126_SANDCASTLE_OPEN_DOOR_EIGHT},
    {VOLATILE_FLAG_7C_SANDCASTLE_PUZZLE_COMPLETE_DOG, FILEPROG_127_SANDCASTLE_PUZZLE_COMPLETE_DOG},
#endif
    {VOLATILE_FLAG_65_CHEAT_ENTERED, FILEPROG_123_CHEAT_ENTERED},
    {-1, 0x000}
};

/* .bss */
s32 baseOffset;
s32 jiggyOffset;
s32 honeycombOffset;
s32 mumbotokenOffset;
s32 notescoresOffset;
s32 timescoresOffset;
s32 progressflagsOffset;
s32 savedItemsOffset;
s32 abilitiesOffset;
#ifdef NOTE_SAVING
s32 notesavingOffset;
#endif
#ifdef JINJO_SAVING
s32 jinjosavingOffset;
s32 jinjojiggyrespawnOffset;
#endif
s32 endOffset;
u8 D_80383D18[8];

/* .code */
void savedata_update_crc(s32 buffer, s32 size){
    u32 sp20[2];
    u32 sum;
    glcrc_calc_checksum(buffer, buffer + size - 4, sp20);
    sum = sp20[0] ^ sp20[1];
    *(u32*)(buffer + size - 4) = sum;
}

int _savedata_verify(SaveData *savedata, s32 size){
    u32 result[2]; //sp28
    u32 *crc_ptr;
    u32 expect_crc; //sp20

    crc_ptr = (u32*)((s32)savedata + size) - 1;
    expect_crc = *crc_ptr;
    glcrc_calc_checksum(savedata, crc_ptr, result);
    *crc_ptr = expect_crc;
    if((result[0]^result[1]) != expect_crc) 
        return 0x6e382;
    return 0;
}

void savedata_init(void){ //savedata_init
    s32 jiggy_size;
    s32 honeycomb_size;
    s32 mumbotoken_size;
    s32 notescores_size = 0;
    s32 timescores_size = 0;
    s32 progressflags_size;
    s32 saved_item_size;
    s32 abilities_size;
#ifdef NOTE_SAVING
    s32 notesaving_size;
#endif
#ifdef JINJO_SAVING
    s32 jinjosaving_size;
    s32 jinjojiggyrespawn_size;
#endif
    u8 *jiggy_addr;
    u8 *honeycomb_addr;
    u8 *mumbotoken_addr;
    u8 *progressflags_addr;
    u8 *notescores_addr;
    u8 *timescores_addr;
    u8 *saved_item_addr;
    u8 *abilities_addr;
#ifdef NOTE_SAVING
    u8 *notesaving_addr;
#endif
#ifdef JINJO_SAVING
    u8 *jinjosaving_addr;
    u8 *jinjojiggyrespawn_addr;
#endif

    s32 prevOffset;
    s32 prevSize;
    
    jiggyscore_getSizeAndPtr(&jiggy_size, &jiggy_addr);
    honeycombscore_getSizeAndPtr(&honeycomb_size, &honeycomb_addr);
    mumboscore_getSizeAndPtr(&mumbotoken_size, &mumbotoken_addr);
    fileProgressFlag_getSizeAndPtr(&progressflags_size, &progressflags_addr);
    notescore_getSizeAndPtr(&notescores_size, &notescores_addr);
    timeScores_getSizeAndPtr(&timescores_size, &timescores_addr);
    saveditem_getSizeAndPtr(&saved_item_size, &saved_item_addr);
    ability_getSizeAndPtr(&abilities_size, &abilities_addr);
#ifdef NOTE_SAVING
    notesaving_getSizeAndPtr(&notesaving_size, &notesaving_addr);
#endif
#ifdef JINJO_SAVING
    jinjosaving_getSizeAndPtr(&jinjosaving_size, &jinjosaving_addr);
    jinjojiggyrespawn_getSizeAndPtr(&jinjojiggyrespawn_size, &jinjojiggyrespawn_addr);
#endif
    baseOffset = 0;
    jiggyOffset = baseOffset + 2;
    honeycombOffset = jiggyOffset + jiggy_size;
    mumbotokenOffset = honeycombOffset + honeycomb_size;
    notescoresOffset = mumbotokenOffset + mumbotoken_size;
    timescoresOffset = notescoresOffset + notescores_size;
    progressflagsOffset = timescoresOffset + timescores_size;
    savedItemsOffset = progressflagsOffset + progressflags_size;
    abilitiesOffset = savedItemsOffset + saved_item_size;

    prevOffset = abilitiesOffset;
    prevSize = abilities_size;

#ifdef NOTE_SAVING
    notesavingOffset = prevOffset + prevSize;
    prevOffset = notesavingOffset;
    prevSize = notesaving_size;
#endif
#ifdef JINJO_SAVING
    jinjosavingOffset = prevOffset + prevSize;
    jinjojiggyrespawnOffset = jinjosavingOffset + jinjosaving_size;
    prevOffset = jinjojiggyrespawnOffset;
    prevSize = jinjojiggyrespawn_size;
#endif
    endOffset = prevOffset + prevSize;
}

void __savedata_load_jiggyScore(u8 *savedata){
    s32 jiggy_size;
    u8 *jiggy_addr;
    int i;
    
    jiggyscore_getSizeAndPtr(&jiggy_size, &jiggy_addr);
    for(i = jiggyOffset; i < jiggyOffset + jiggy_size; i++){
        jiggy_addr[i - jiggyOffset] = savedata[i];
    }
    func_8034798C();
}

void __savedata_load_honeycombScore(u8 *savedata){ //savedata_save_honeycomb
    s32 honeycomb_size;
    u8 *honeycomb_addr;
    int i;
    
    honeycombscore_getSizeAndPtr(&honeycomb_size, &honeycomb_addr);
    for(i = honeycombOffset; i < honeycombOffset + honeycomb_size; i++){
        honeycomb_addr[i - honeycombOffset] = savedata[i];
    }
    func_80347958();
}

void __savedata_load_mumboScore(u8 *savedata){
    s32 mumbotoken_size;
    u8 *mumbotoken_addr;
    int i;
    
    mumboscore_getSizeAndPtr(&mumbotoken_size, &mumbotoken_addr);
    for(i = mumbotokenOffset; i < mumbotokenOffset + mumbotoken_size; i++){
        mumbotoken_addr[i - mumbotokenOffset] = savedata[i];
    }
    func_80347984();
}

void __savedata_load_highNoteScores(u8 *savedata){
    s32 notescores_size;
    u8 *notescores_addr;
    int i;
    
    notescore_getSizeAndPtr(&notescores_size, &notescores_addr);
    for(i = notescoresOffset; i < notescoresOffset + notescores_size; i++){
        notescores_addr[i - notescoresOffset] = savedata[i];
    }
    itemscore_highNoteScores_fromSaveData(notescores_addr);
}

void __savedata_load_timeScores(u8 *savedata){
    s32 timescores_size;
    u8 *timescores_addr;
    int i;
    
    timeScores_getSizeAndPtr(&timescores_size, &timescores_addr);
    for(i = timescoresOffset; i < timescoresOffset + timescores_size; i++){
        timescores_addr[i - timescoresOffset] = savedata[i];
    }
    itemscore_timeScores_fromSaveData(timescores_addr);
}

void func_8033C460(u8 *savedata){ //global_progress
    s32 progressflags_size;
    u8 *progressflags_addr;
    int i;
    
    fileProgressFlag_getSizeAndPtr(&progressflags_size, &progressflags_addr);
    for(i = progressflagsOffset; i < progressflagsOffset + progressflags_size; i++){
        progressflags_addr[i - progressflagsOffset] = savedata[i];
    }
}

void func_8033C4E4(u8 *savedata){ //saveddata_load_collectibles
    s32 saved_item_size;
    u8 *saved_item_addr;
    int i;
    
    saveditem_getSizeAndPtr(&saved_item_size, &saved_item_addr);
    for(i = savedItemsOffset; i < savedItemsOffset + saved_item_size; i++){
        saved_item_addr[i - savedItemsOffset] = savedata[i];
    }
    func_803479C0(saved_item_addr);
}

void __savedata_load_abilities(u8 *savedata){ //savedata_load_abilities
    s32 abilities_size;
    u8 *abilities_addr;
    int i;
    
    ability_getSizeAndPtr(&abilities_size, &abilities_addr);
    for(i = abilitiesOffset; i < abilitiesOffset + abilities_size; i++){
        abilities_addr[i - abilitiesOffset] = savedata[i];
    }
}

#ifdef NOTE_SAVING
void __savedata_load_notesavings(u8 *savedata){
    s32 notesaving_size;
    u8 *notesaving_addr;
    int i;
    
    notesaving_getSizeAndPtr(&notesaving_size, &notesaving_addr);
    for(i = notesavingOffset; i < notesavingOffset + notesaving_size; i++){
        notesaving_addr[i - notesavingOffset] = savedata[i];
    }
}
#endif

#ifdef JINJO_SAVING
void __savedata_load_jinjosavings(u8 *savedata){
    s32 jinjosaving_size;
    u8 *jinjosaving_addr;
    int i;
    
    jinjosaving_getSizeAndPtr(&jinjosaving_size, &jinjosaving_addr);
    for(i = jinjosavingOffset; i < jinjosavingOffset + jinjosaving_size; i++){
        jinjosaving_addr[i - jinjosavingOffset] = savedata[i];
    }
}

void __savedata_load_jinjojiggyrespawns(u8 *savedata){
    s32 jinjojiggyrespawn_size;
    u8 *jinjojiggyrespawn_addr;
    int i;
    
    jinjojiggyrespawn_getSizeAndPtr(&jinjojiggyrespawn_size, &jinjojiggyrespawn_addr);
    for(i = jinjojiggyrespawnOffset; i < jinjojiggyrespawnOffset + jinjojiggyrespawn_size; i++){
        jinjojiggyrespawn_addr[i - jinjojiggyrespawnOffset] = savedata[i];
    }
}
#endif

void __savedata_save_magic(u8 *savedata){
    savedata[baseOffset] = 0x11;
}

void __savedata_save_jiggyScore(u8 *savedata){ //savedata_save_jiggies
    s32 jiggy_size;
    u8 *jiggy_addr;
    int i;
    
    jiggyscore_getSizeAndPtr(&jiggy_size, &jiggy_addr);
    for(i = jiggyOffset; i < jiggyOffset + jiggy_size; i++){
        savedata[i] = jiggy_addr[i - jiggyOffset];
    }
}

void __savedata_save_honeycombScore(u8 *savedata){ //savedata_save_honeycomb
    s32 honeycomb_size;
    u8 *honeycomb_addr;
    int i;
    
    honeycombscore_getSizeAndPtr(&honeycomb_size, &honeycomb_addr);
    for(i = honeycombOffset; i < honeycombOffset + honeycomb_size; i++){
        savedata[i] = honeycomb_addr[i - honeycombOffset];
    }
}

void __savedata_save_mumboScore(u8 *savedata){
    s32 mumbotoken_size;
    u8 *mumbotoken_addr;
    int i;
    
    mumboscore_getSizeAndPtr(&mumbotoken_size, &mumbotoken_addr);
    for(i = mumbotokenOffset; i < mumbotokenOffset + mumbotoken_size; i++){
        savedata[i] = mumbotoken_addr[i - mumbotokenOffset];
    }
}

void __savedata_save_highNoteScores(u8 *savedata){
    s32 notescores_size;
    u8 *notescores_addr;
    int i;
    
    notescore_getSizeAndPtr(&notescores_size, &notescores_addr);
    for(i = notescoresOffset; i < notescoresOffset + notescores_size; i++){
        savedata[i] = notescores_addr[i - notescoresOffset];
    }
}

void __savedata_save_timeScores(u8 *savedata){
    s32 timescores_size;
    u8 *timescores_addr;
    int i;
    
    timeScores_getSizeAndPtr(&timescores_size, &timescores_addr);
    for(i = timescoresOffset; i < timescoresOffset + timescores_size; i++){
        savedata[i] = timescores_addr[i - timescoresOffset];
    }
}

void __savedata_8033C8A0(u8 *savedata){ //global_progress
    s32 progressflags_size;
    u8 *progressflags_addr;
    int i;
    
    fileProgressFlag_getSizeAndPtr(&progressflags_size, &progressflags_addr);
    for(i = progressflagsOffset; i < progressflagsOffset + progressflags_size; i++){
        savedata[i] = progressflags_addr[i - progressflagsOffset];
    }
}

void __savedata_8033CA2C(u8 *savedata){ //saveddata_save_collectibles
    s32 saved_item_size;
    u8 *saved_item_addr;
    int i;
    
    saveditem_getSizeAndPtr(&saved_item_size, &saved_item_addr);
    for(i = savedItemsOffset; i < savedItemsOffset + saved_item_size; i++){
        savedata[i] = saved_item_addr[i - savedItemsOffset];
    }
}

void __savedata_save_abilities(u8 *savedata){ //savedata_save_abilities
    s32 abilities_size;
    u8 *abilities_addr;
    int i;
    
    ability_getSizeAndPtr(&abilities_size, &abilities_addr);
    for(i = abilitiesOffset; i < abilitiesOffset + abilities_size; i++){
        savedata[i] = abilities_addr[i - abilitiesOffset];
    }
}

#ifdef NOTE_SAVING
void __savedata_save_notesavings(u8 *savedata){
    s32 notesaving_size;
    u8 *notesaving_addr;
    int i;
    
    notesaving_getSizeAndPtr(&notesaving_size, &notesaving_addr);
    for(i = notesavingOffset; i < notesavingOffset + notesaving_size; i++){
        savedata[i] = notesaving_addr[i - notesavingOffset];
    }
}
#endif

#ifdef JINJO_SAVING
void __savedata_save_jinjosavings(u8 *savedata){
    s32 jinjosaving_size;
    u8 *jinjosaving_addr;
    int i;
    
    jinjosaving_getSizeAndPtr(&jinjosaving_size, &jinjosaving_addr);
    for(i = jinjosavingOffset; i < jinjosavingOffset + jinjosaving_size; i++){
        savedata[i] = jinjosaving_addr[i - jinjosavingOffset];
    }
}

void __savedata_save_jinjojiggyrespawns(u8 *savedata){
    s32 jinjojiggyrespawn_size;
    u8 *jinjojiggyrespawn_addr;
    int i;
    
    jinjojiggyrespawn_getSizeAndPtr(&jinjojiggyrespawn_size, &jinjojiggyrespawn_addr);
    for(i = jinjojiggyrespawnOffset; i < jinjojiggyrespawnOffset + jinjojiggyrespawn_size; i++){
        savedata[i] = jinjojiggyrespawn_addr[i - jinjojiggyrespawnOffset];
    }
}
#endif

s32 savedata_8033CA2C(s32 filenum, SaveData *save_data){
    s32 sp1C;
    
#ifdef EEPROM_16K
    sp1C = eeprom_readBlocks(filenum, 0, save_data, 0x1F); // Reads data from game file
#else
    sp1C = eeprom_readBlocks(filenum, 0, save_data, 0xF);
#endif
    if( sp1C 
#ifdef EEPROM_16K
        || savedata_verify(0xF8, save_data) 
#else
        || savedata_verify(0x78, save_data) 
#endif
        || ((u8*)save_data)[baseOffset] != 0x11
    ){
        sp1C = 2;
    }
    return sp1C;
}

s32 savedata_8033CA9C(SaveData *savedata){
    s32 sp1C;
    
#ifdef EEPROM_16K
    sp1C = eeprom_readBlocks(0, 0xFC, savedata, 0x4); // Reads Stop n' Swop data
#else
    sp1C = eeprom_readBlocks(0, 0x3C, savedata, 0x4);
#endif
    if( sp1C 
        || savedata_verify(0x20, savedata) 
    ){
        sp1C = 2;
    }
    return sp1C;
}

s32 savedata_verify(s32 size, SaveData *savedata){
    s32 v1;

    v1 = _savedata_verify(savedata, size);
    if(v1)
        v1 = 3;
    return v1;
}

void saveData_load(SaveData *savedata){
    int i;
    func_8033C460(savedata);
    __savedata_load_jiggyScore(savedata);
    __savedata_load_honeycombScore(savedata);
    __savedata_load_mumboScore(savedata);
    __savedata_load_highNoteScores(savedata);
    __savedata_load_timeScores(savedata);
    func_8033C4E4(savedata);
    __savedata_load_abilities(savedata);
#ifdef NOTE_SAVING
    __savedata_load_notesavings(savedata);
#endif
#ifdef JINJO_SAVING
    __savedata_load_jinjosavings(savedata);
    __savedata_load_jinjojiggyrespawns(savedata);
#endif
    for(i = 0; D_80370A20[i].unk0 != -1; i++){
        volatileFlag_set(D_80370A20[i].unk0, fileProgressFlag_get(D_80370A20[i].unk2));
    }
}

void saveData_create(SaveData *savedata){
    int i;
    for(i = 0; D_80370A20[i].unk0 != -1; i++){
        fileProgressFlag_set(D_80370A20[i].unk2, volatileFlag_get(D_80370A20[i].unk0));
    }
    savedata_clear(savedata);
    __savedata_save_magic(savedata);
    __savedata_save_jiggyScore(savedata);
    __savedata_save_honeycombScore(savedata);
    __savedata_save_mumboScore(savedata);
    __savedata_save_highNoteScores(savedata);
    __savedata_save_timeScores(savedata);
    __savedata_8033C8A0(savedata);
    __savedata_8033CA2C(savedata);
    __savedata_save_abilities(savedata);
#ifdef NOTE_SAVING
    __savedata_save_notesavings(savedata);
#endif
#ifdef JINJO_SAVING
    __savedata_save_jinjosavings(savedata);
    __savedata_save_jinjojiggyrespawns(savedata);
#endif
    savedata_update_crc(savedata, sizeof(SaveData));
}

int savedata_8033CC98(s32 filenum, u8 *buffer){
    int out;
#ifdef EEPROM_16K
    out = eeprom_writeBlocks(filenum, 0, buffer, 0x1F); // Writes data to game file
#else
    out = eeprom_writeBlocks(filenum, 0, buffer, 0xF);
#endif
    if(out){
        out = 1;
    }
    return out;
}

int savedata_8033CCD0(s32 filenum){
    int out;
    out = eeprom_writeBlocks(filenum, 0, D_80383D18, 1);
    if(out){
        out = 1;
    }
    return out;
}

int savedata_8033CE40(u8 *buffer){
    int out;
    savedata_update_crc(buffer, sizeof(GlobalData));
#ifdef EEPROM_16K
    out = eeprom_writeBlocks(0, 0xFC, buffer, 4); // Writes Stop n' Swop data to the very end of 16k-EEPROM
#else
    out = eeprom_writeBlocks(0, 0x3C, buffer, 4);
#endif
    if(out){
        out = 1;
    }
    return out;
}

void savedata_clear(u8 *savedata){
    int i;
    for(i = 0; i < sizeof(SaveData); i++){
        savedata[i] = 0;
    }
}
