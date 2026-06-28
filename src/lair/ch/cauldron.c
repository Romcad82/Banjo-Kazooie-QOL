#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#include "config.h"
#include "src/core2/gc/zoombox.h"

extern void func_8028F4B8(f32[3], f32, f32);
extern void func_8028F66C(s32);
extern void func_802D6310(f32, enum map_e, s32, s32, enum file_progress_e);
extern void func_802EE354(Actor *, s32, s32, s32, f32, f32, f32, s32[4], s32, s32);
extern void func_80324CFC(f32, enum comusic_e, s32);
extern void func_8034DF30(s32, f32[4], f32[4], f32);
#ifdef WARP_CAULDRON_MENU
extern void set_menu_finished_displaying_state(bool setState);
extern  f32 func_80309B24(f32[3]);
#endif

/* .h */
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 pad4[0x2];
    s16 unk6;
}Struct_lair_42A0_0;

void chWarpCauldron_update(Actor *this);
Actor *chWarpCauldron_draw(ActorMarker *marker, Gfx **gfx, Mtx **mtx, Vtx **vtx);
#ifdef WARP_CAULDRON_MENU
void open_warpMenu_zoomboxes(enum file_progress_e currFlag);
void update_warpMenu_zoombox_data(enum file_progress_e currFlag);
void warpMenu_zoomboxFree(void);
void reopen_warpMenu_zoomboxes(enum file_progress_e currFlag);
#endif

/* .data */
ActorAnimationInfo D_80393520[] = {
    {    0, 0.0f},
    {0x213, 2.66f},
    {0x212, 2.0f},
    {0x214, 6.4f},
    {0x215, 3.4f},
    {0x216, 1.0f},
    {0x28F, 5.167f},
    {0x290, 6.26f}
#ifdef WARP_CAULDRON_MENU
    ,
    {0x216, 1.0f}, // State 8
    {0x214, 6.4f}  // State 9
#endif
};
ActorInfo D_80393560 = { MARKER_231_WARP_CAULDRON, ACTOR_23B_WARP_CAULDRON, ASSET_4DF_MODEL_WARP_CAULDRON, 1, D_80393520, chWarpCauldron_update, actor_update_func_80326224, chWarpCauldron_draw, 0, 0, 3.0f, 0};
ActorInfo D_80393584 = { MARKER_244_DINGPOT, ACTOR_2DB_DINGPOT, ASSET_450_MODEL_DINGPOT, 1, D_80393520, chWarpCauldron_update, actor_update_func_80326224, chWarpCauldron_draw, 0, 0, 3.0f, 0};
f32 D_803935A8[][2][3] = {
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}, 
    {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}}, 
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.4f, 0.0f}}, 
    {{1.0f, 1.0f, 1.0f}, {0.3f, 0.6f, 1.0f}}, 
    {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}
};
#ifdef WARP_CAULDRON_MENU
u8 cauldronTextColors[5][3] = {
    {0xFF, 0x00, 0x85}, // Pink Cauldron
    {0x00, 0xE5, 0x61}, // Green Cauldron
    {0xFF, 0x60, 0x00}, // Red Cauldron
    {0x00, 0x5F, 0xB8}, // Blue Cauldron (Unused)
    {0xFF, 0xE0, 0x00}  // Yellow Cauldron
};
#endif

Struct_lair_42A0_0 D_80393620[] = {
    {MAP_6A_GL_TTC_AND_CC_PUZZLE, 0x5A, 0x8, 0x72, 0x62, 0x6A, 0x240},
    {MAP_6F_GL_FP_LOBBY,          0x5B, 0x8, 0x73, 0x63, 0x6B, 0x240},
    {MAP_6F_GL_FP_LOBBY,          0x5C, 0x9, 0x74, 0x64, 0x6C, 0x241},
    {MAP_77_GL_RBB_LOBBY,         0x5D, 0x8, 0x75, 0x65, 0x6D, 0x240},
    {MAP_6C_GL_RED_CAULDRON_ROOM, 0x5E, 0x8, 0x76, 0x66, 0x6E, 0x240},
    {MAP_79_GL_CCW_LOBBY,         0x5F, 0x8, 0x77, 0x67, 0x6F, 0x240},
    {MAP_93_GL_DINGPOT,           0x60, 0x0, 0x78, 0x68, 0x70, 0x240},
    {0,                           0x61, 0x0, 0x79, 0x69, 0x71, 0x240},
    {MAP_8E_GL_FURNACE_FUN,       0x8A, 0x8, 0x90, 0x8C, 0x8E, 0x240},
    {MAP_93_GL_DINGPOT,           0x8B, 0x8, 0x91, 0x8D, 0x8F, 0x241}
};

#ifdef WARP_CAULDRON_MENU
static const scrollingMenuZoomboxFormat cauldronZoomboxData[] = {
 #ifndef GENERIC_CAULDRON_NAMES
    {FILEPROG_49_PINK_CAULDRON_1_ACTIVE,   "2ND FLOOR",        "",            ZOOMBOX_SPRITE_57_BRENTILDA,  NULL},
    {FILEPROG_4A_PINK_CAULDRON_2_ACTIVE,   "FREEZEEZY PEAK",   "LOWER LOBBY", ZOOMBOX_SPRITE_44_WOZZA,      NULL},
    {FILEPROG_4B_GREEN_CAULDRON_1_ACTIVE,  "FREEZEEZY PEAK",   "UPPER LOBBY", ZOOMBOX_SPRITE_43_BOGGY,      NULL},
    {FILEPROG_4C_GREEN_CAULDRON_2_ACTIVE,  "RUSTY BUCKET BAY", "LOBBY",       ZOOMBOX_SPRITE_3E_SNORKEL,    NULL},
    {FILEPROG_4D_RED_CAULDRON_1_ACTIVE,    "PIPE ROOM",        "",            ZOOMBOX_SPRITE_39_GLOOP,      NULL},
    {FILEPROG_4E_RED_CAULDRON_2_ACTIVE,    "CLICK CLOCK WOOD", "LOBBY",       ZOOMBOX_SPRITE_4D_GNAWTY,     NULL},
    {FILEPROG_51_YELLOW_CAULDRON_1_ACTIVE, "FURNACE FUN",      "",            ZOOMBOX_SPRITE_7_TOOTY_1,     NULL},
    {FILEPROG_52_YELLOW_CAULDRON_2_ACTIVE, "TOP OF THE TOWER", "",            ZOOMBOX_SPRITE_5_GRUNTILDA_2, NULL},
    {FILEPROG_4F_UNUSED_CAULDRON_1_ACTIVE, "DINGPOT",          "",            0x64,                         NULL}, // Some enum names in 'zoombox.h' are wrong. 0x64 are Dingpot's sprites.
    {FILEPROG_50_UNUSED_CAULDRON_2_ACTIVE, "UNUSED",           "",            ZOOMBOX_SPRITE_4_BANJO_1,     NULL}
 #else
    {FILEPROG_49_PINK_CAULDRON_1_ACTIVE,   "PINK CAULDRON A",   "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4A_PINK_CAULDRON_2_ACTIVE,   "PINK CAULDRON B",   "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4B_GREEN_CAULDRON_1_ACTIVE,  "GREEN CAULDRON A",  "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4C_GREEN_CAULDRON_2_ACTIVE,  "GREEN CAULDRON B",  "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4D_RED_CAULDRON_1_ACTIVE,    "RED CAULDRON A",    "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4E_RED_CAULDRON_2_ACTIVE,    "RED CAULDRON B",    "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_51_YELLOW_CAULDRON_1_ACTIVE, "YELLOW CAULDRON A", "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_52_YELLOW_CAULDRON_2_ACTIVE, "YELLOW CAULDRON B", "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_4F_UNUSED_CAULDRON_1_ACTIVE, "BLUE CAULDRON A",   "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL},
    {FILEPROG_50_UNUSED_CAULDRON_2_ACTIVE, "BLUE CAULDRON B",   "", ZOOMBOX_SPRITE_56_WARP_CAULDRON, NULL}
 #endif
};
#endif

f32 D_80393670[] = {0.083f, 0.202f, 0.285f, 0.371f, 0.417f, -1.0f};
f32 D_80393688[] = {0.571f, 0.608f, 0.645f, 0.685f, 0.716f, 0.75f, 0.791f, -1.0f};
f32 D_803936A8[] = {0.293f, 0.376f, 0.42f, 0.453f, 0.488f, 0.522f, 0.556f, 0.59f, 0.626f, 0.661f, 0.693f, 0.729f, 0.764f, 0.863f, -1.0f}; 
f32 D_803936E4[] = {0.03f, 0.09f, 0.2f, 0.25f, 0.32f, 0.4f, 0.45f, 1.0f};

#ifdef WARP_CAULDRON_MENU
u8 *WARP_GENERAL_INSTRUCTIONS = "CHOOSE A DESTINATION YOU WANT TO WARP TO.";
u8 *WARP_INSTRUCTIONS_A_BUTTON = "PRESS A TO MAKE A SELECTION.";
u8 *WARP_INSTRUCTIONS_L_BUTTON = "PRESS L TO VIEW THE WARP LOCATION.";
u8 *WARP_INSTRUCTIONS_B_BUTTON = "PRESS B TO HOP OUT OF THE CAULDRON.";

extern scrollingMenuStruct scrollingMenu;

u32 currCauldronID = 0;
u32 targetCauldronID = 0;
u32 warpCheck = 0;
bool currCauldronUnderwater = FALSE;
bool skipUnderwaterCheck = FALSE;
#endif

/* .code */
bool func_8038A690(Actor *this) {
    if (this->actorTypeSpecificField != 3) {
        return subaddie_playerIsWithinCylinder(this, 400, 90);
    }
    else{
        return subaddie_playerIsWithinAsymmetricCylinder(this, 500, 260, 90);
    }
}

enum file_progress_e chWarpCauldron_getFileProgressFlagIndex(Actor *this){
    return this->actorTypeSpecificField -1 + 0x49;
}

enum file_progress_e chWarpCauldron_getPairedFileProgressFlagIndex(Actor *this){
    return ((this->actorTypeSpecificField - 1) ^ 1) + 0x49;
}

void func_8038A704(Actor *this){
    subaddie_set_state_with_direction(this, 3, 0.99f, 1);
}

void func_8038A730(Actor *this, f32 *arg1, enum sfx_e arg2, enum sfx_e arg3, u32 arg4) {
    s32 i;

    for(i = 0; arg1[i] != -1.0f; i++){
        if (actor_animationIsAt(this, arg1[i])) {
            if (arg3 != SFX_0_BLOOP) {
                func_8030E878((randf() < 0.5) ? arg2 : arg3, randf2(1.0f, 1.1f), arg4, this->position, 0.0f, 1200.0f);
            }
            else{
                func_8030E878(arg2, 1.0f, arg4, this->position, 0.0f, 1200.0f);
            }
            return;
        }
    }
}

void lair_func_8038A864(Actor *this) {
    switch (this->state) {
    case 2:
        func_8038A730(this, D_80393670, SFX_3F_CAULDRON_SQUEAK_1, SFX_40_CAULDRON_SQUEAK_2, 11000);
        break;
    case 3:
        func_8038A730(this, D_80393688, SFX_3F_CAULDRON_SQUEAK_1, SFX_40_CAULDRON_SQUEAK_2, 11000);
        break;
    case 5:
        if (actor_animationIsAt(this, 0.5f)) {
            FUNC_8030E624(SFX_C5_TWINKLY_POP, 0.8f, 32000);

        }
        if (actor_animationIsAt(this, 0.596f)) {
            FUNC_8030E624(SFX_2D_KABOING, 0.85f, 32000);
        }
        break;
    case 4:
        func_8038A730(this, D_803936A8, SFX_3F_CAULDRON_SQUEAK_1, SFX_40_CAULDRON_SQUEAK_2, 11000);
        break;
#ifdef WARP_CAULDRON_MENU
    case 9:
        func_8038A730(this, D_80393688, SFX_3F_CAULDRON_SQUEAK_1, SFX_40_CAULDRON_SQUEAK_2, 11000);
        break;
#endif
    }
}

void func_8038A96C(Actor *this, s32 arg1) {
    s32 sp5C;
    s32 i;
    f32 sp48[4];
    f32 sp38[4];

    if( ( (arg1 != 3) || ( (this->unk1C[1] == 0.0f) && (this->marker->unk14_21 == 1))) 
        && (this->modelCacheIndex == ACTOR_23B_WARP_CAULDRON) 
        && ((arg1 != 0) || fileProgressFlag_get(chWarpCauldron_getFileProgressFlagIndex(this))) 
    ){
        sp5C = func_8034C2C4(this->marker, 0x1C3);
        if(sp5C != 0){
            for(i = 0; i < 3; i++){
                sp48[i] = D_803935A8[(((s32)this->actorTypeSpecificField - 1)>>1)][0][i];
                sp38[i] = D_803935A8[(((s32)this->actorTypeSpecificField - 1)>>1)][1][i];

            }
            sp48[3] = 1.0f;
            sp38[3] = 1.0f;
            if (arg1 == 2) {
                func_8034DF30(sp5C, sp38, sp38, 0.3f);
            }
            else{
                func_8034DF30(sp5C, sp48, sp38, fileProgressFlag_get(chWarpCauldron_getFileProgressFlagIndex(this)) ? 0.3 : 3.0);
            }
        }
    }
}

void func_8038AB90(Actor *this, s32 arg1, s32 arg2, enum sfx_e sfx_id, f32 sfx_timing) {
    if (arg2 == this->unk10_12) {
        if (this->actorTypeSpecificField == 7) {
            func_80324CFC(0.5f, COMUSIC_8C_JINJONATOR_POWERUP, 32000);
            func_80324D2C(7.0f, COMUSIC_8C_JINJONATOR_POWERUP);
        }
        this->unk10_12 = 0;
        subaddie_set_state_forward(this, arg1);
        actor_playAnimationOnce(this);
        func_8028FCBC();
        if (sfx_id != SFX_0_BLOOP) {
            timed_playSfx(sfx_timing, sfx_id, 1.0f, 32000);
            if (arg2 == 2
#ifdef WARP_CAULDRON_MENU
                && (arg1 != 8)
#endif
                ) {
                coMusicPlayer_playMusicWeak(COMUSIC_3F_MAGIC_CARPET_RISING, 32000);
                func_80324D2C(2.6f, COMUSIC_3F_MAGIC_CARPET_RISING);
// Don't need to play SFX_7C_CHEBOOF like this anymore. Only play when it's sfx_id.
#ifndef WARP_CAULDRON_MENU
                gcsfx_play(SFX_7C_CHEBOOF);
#elif defined(OPTIONS_MENU)
                if (!is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU)) {
                    gcsfx_play(SFX_7C_CHEBOOF);
                }
#endif
            }
        }
    }
}
void func_8038AC7C(Actor *this) {
    s32 sp2C;
    u32 sp28;

    if(
        (gcdialog_getCurrentTextId() != 0xFAD)
        && subaddie_playerIsWithinSphereAndActive(this, 1200)
        && !fileProgressFlag_get(FILEPROG_FC_DEFEAT_GRUNTY)
    ) {
        this->lifetime_value += time_getDelta();
        if (35.0 < this->lifetime_value) {
            sp2C = (fileProgressFlag_get(FILEPROG_CF_HAS_ENTERED_FINAL_FIGHT)) ? 0xFB7 : 0xFAE;
            sp28 = (fileProgressFlag_get(FILEPROG_CF_HAS_ENTERED_FINAL_FIGHT)) ? 0xFBC : 0xFB7;
            if (gcdialog_showDialog(sp2C + this->unk38_31, 0, NULL, NULL, NULL, NULL)) {
                this->unk38_31++;
                this->lifetime_value = 0.0f;
                if (sp2C + this->unk38_31 >= sp28) {
                    this->unk38_31 = 0;
                }
            }
        }
    }
}


void __chWarpCauldron_dingpotDialogCallback(ActorMarker *marker, enum asset_e text_id, s32 arg2){
    fileProgressFlag_set(FILEPROG_F3_MET_DINGPOT, TRUE);
}

bool lair_func_8038ADF0(s32 arg0, s32 arg1) {
    s32 phi_v1;

    phi_v1 = arg1 - arg0;
    while (phi_v1 < 0)    { phi_v1 += 360; }
    while (phi_v1 >= 360) { phi_v1 -= 360;}
    return phi_v1 < 70;
}

#ifdef WARP_CAULDRON_MENU
bool count_total_active_cauldrons(void) {
    u8 cauldronActiveCount = 0;
    u8 i;
    for (i = 0; i < 10; i++) {
        cauldronActiveCount += (u8)fileProgressFlag_get(cauldronZoomboxData[i].id);
    }
    return cauldronActiveCount;
}

u16 find_first_available_cauldron_flag(enum file_progress_e currFlag, s16 flagIndex, s8 countDirection, bool returnFlag) {
    while ((0 <= flagIndex) && (flagIndex <= 9)) {
        if (fileProgressFlag_get(cauldronZoomboxData[flagIndex].id) && (cauldronZoomboxData[flagIndex].id != currFlag)) {
            if (returnFlag) {
                return cauldronZoomboxData[flagIndex].id;
            } else {
                return flagIndex;
            }
        }
        flagIndex += countDirection;
    }
}

u8 get_original_cauldron_order_index(u8 index) {
    return cauldronZoomboxData[index].id - 0x49;
}

void set_cauldron_variables_if_different_destination(enum map_e destination, u32 currActorTypeSpecificField, u32 targetActorTypeSpecificField) {
    if (gsworld_getMap() != destination) {
        warpMenu_zoomboxFree();
        currCauldronID = currActorTypeSpecificField;
        targetCauldronID = targetActorTypeSpecificField;
    }
}

void warp_cauldron_cutscene(u32 currActorTypeSpecificField, u16 selection, bool qolSelectionOrder, f32 delay) {
    set_inWarpCauldronCutscene((u8)get_warpMenuActive() + 1);

    if (qolSelectionOrder) {
        static const u16 rearrangedOrder[10] = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9};
        selection = rearrangedOrder[get_original_cauldron_order_index(selection)];
    }

    switch (selection) {
        case 2:
            set_cauldron_variables_if_different_destination(MAP_6A_GL_TTC_AND_CC_PUZZLE, currActorTypeSpecificField, 1);
            func_802D6310(delay, MAP_6A_GL_TTC_AND_CC_PUZZLE, 0x62, 0x22, 0);
            break;

        case 1:
            set_cauldron_variables_if_different_destination(MAP_6F_GL_FP_LOBBY, currActorTypeSpecificField, 2);
            func_802D6310(delay, MAP_6F_GL_FP_LOBBY, 0x63, 0x23, 0);
            break;

        case 4:
            set_cauldron_variables_if_different_destination(MAP_6F_GL_FP_LOBBY, currActorTypeSpecificField, 3);
            func_802D6310(delay, MAP_6F_GL_FP_LOBBY, 0x64, 0x24, 0);
            break;

        case 3:
            set_cauldron_variables_if_different_destination(MAP_77_GL_RBB_LOBBY, currActorTypeSpecificField, 4);
            func_802D6310(delay, MAP_77_GL_RBB_LOBBY, 0x65, 0x25, 0);
            break;

        case 6:
            set_cauldron_variables_if_different_destination(MAP_6C_GL_RED_CAULDRON_ROOM, currActorTypeSpecificField, 5);
            func_802D6310(delay, MAP_6C_GL_RED_CAULDRON_ROOM, 0x66, 0x26, 0);
            break;

        case 5:
            set_cauldron_variables_if_different_destination(MAP_79_GL_CCW_LOBBY, currActorTypeSpecificField, 6);
            func_802D6310(delay, MAP_79_GL_CCW_LOBBY, 0x67, 0x27, 0);
            break;

        case 10:
            set_cauldron_variables_if_different_destination(MAP_8E_GL_FURNACE_FUN, currActorTypeSpecificField, 9);
            func_802D6310(delay, MAP_8E_GL_FURNACE_FUN, 0x8C, 0x29, 0);
            break;

        case 9:
            set_cauldron_variables_if_different_destination(MAP_93_GL_DINGPOT, currActorTypeSpecificField, 10);
            func_802D6310(delay, MAP_93_GL_DINGPOT, 0x8D, 0x2A, 0);
            break;
    }
}

void warpMenu_made_selection(u32 warpingType) {
    set_warpMenuActive(FALSE);
    scrollingMenu_zoomboxFree();
    warpCheck = warpingType;
}

void set_warp_cauldron_pair_completed(void) {
    gcdialog_showDialog(ASSET_F7A_DIALOG_UNKNOWN, 4, NULL, NULL, NULL, NULL);
    fileProgressFlag_set(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET, 1);
}

void warpCauldron_state_1_qol_funcs(Actor *this, enum sfx_e phi_a0) {
    fileProgressFlag_set(chWarpCauldron_getFileProgressFlagIndex(this), 1);
    phi_a0 = (count_total_active_cauldrons() > 1) ? SFX_107_CAULDRON_ACTIVATION_1 : SFX_108_CAULDRON_ACTIVATION_2;
    gcsfx_playAtSampleRate(phi_a0, 32000);
    if (count_total_active_cauldrons() == 1) {
        gcdialog_showDialog(ASSET_F79_DIALOG_UNKNOWN, 4, NULL, NULL, NULL, NULL);
    } else if (count_total_active_cauldrons() == 2) {
        warp_cauldron_cutscene(this->actorTypeSpecificField, find_first_available_cauldron_flag(chWarpCauldron_getFileProgressFlagIndex(this), 0, 1, FALSE), TRUE, 2.0f);
    // If for whatever reason you activate 2 Cauldrons but FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET doesn't save, then set it when you activate another Cauldron.
    } else if ((count_total_active_cauldrons() >= 3) && !fileProgressFlag_get(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET)) {
        timedFunc_set_0(3.0f, (GenFunction_0) set_warp_cauldron_pair_completed);
    }
}

 #ifdef OPTIONS_MENU
void warpCauldron_state_1_vanilla_funcs(Actor *this, enum sfx_e phi_a0) {
    phi_a0 = (fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this)) != 0) ? SFX_107_CAULDRON_ACTIVATION_1 : SFX_108_CAULDRON_ACTIVATION_2;
    gcsfx_playAtSampleRate(phi_a0, 32000);
    if (!fileProgressFlag_get(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET) && !fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this))) {
        gcdialog_showDialog(ASSET_F79_DIALOG_UNKNOWN, 4, NULL, NULL, NULL, NULL);
    }
    if (fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this))){
        warp_cauldron_cutscene(this->actorTypeSpecificField, this->actorTypeSpecificField, FALSE, 2.0f);
    }
}
 #endif

void close_hud_and_dialog(void) {
    // Closes Hud
    func_802FAD64(ITEM_16_LIFE);
    func_802FAD64(ITEM_14_HEALTH);
    func_802FAD64(ITEM_17_AIR);
    func_802FAD64(ITEM_C_NOTE);
    func_802FAD64(ITEM_D_EGGS);
    func_802FAD64(ITEM_F_RED_FEATHER);
    func_802FAD64(ITEM_10_GOLD_FEATHER);
    func_802FAD64(ITEM_26_JIGGY_TOTAL);
    func_802FAD64(ITEM_25_MUMBO_TOKEN_TOTAL);
    func_802FAD64(ITEM_12_JINJOS);
    func_802FAD64(0x28);
    func_802FAD64(0x29);
    func_802FAD64(ITEM_0_HOURGLASS_TIMER);
    func_802FAD64(ITEM_3_PROPELLOR_TIMER);
    func_802FAD64(ITEM_13_EMPTY_HONEYCOMB);
    func_802FAD64(ITEM_1B_VILE_VILE_SCORE);
    func_802FAD64(ITEM_24_TWINKLY_SCORE);
    func_802FAD64(ITEM_1D_GRUMBLIE);
    func_802FAD64(ITEM_1E_YUMBLIE);
    func_802FAD64(ITEM_E_JIGGY);
    func_802FAD64(ITEM_1C_MUMBO_TOKEN);
    func_802FAD64(ITEM_1A_PLAYER_VILE_SCORE);

    // Closes Dialog
    func_803114D0();
}

void stop_all_timers(void) {
    int i;
    for (i = 0; i < 6; i++) {
        item_adjustByDiffWithoutHud((ITEM_0_HOURGLASS_TIMER + i), 0 - item_getCount(ITEM_0_HOURGLASS_TIMER + i));
        item_adjustByDiffWithoutHud((ITEM_6_HOURGLASS + i), 0 - item_getCount(ITEM_6_HOURGLASS + i));
    }
}

// Needed so music knows when to transition to the underwater variant when you're in a Cauldron.
void check_if_currCauldron_is_underwater(Actor *this) {
    if (currCauldronID != this->actorTypeSpecificField) {
        return;
    }
    // For the first frame the Cauldron is active, it isn't considered to be underwater. This causes issues with the music, so just skip the check when it is initialized.
    if (skipUnderwaterCheck) {
        skipUnderwaterCheck = FALSE;
        return;
    }
    if ((this->position[1] + 100.0f) < func_80309B24(this->position)) {
        currCauldronUnderwater = TRUE;
        return;
    }
    currCauldronUnderwater = FALSE;
}

bool get_currCauldronUnderwater(void) {
    return currCauldronUnderwater;
}
#endif

void chWarpCauldron_update(Actor *this) {
    f32 sp54[3];
    s32 sp50;
    s32 sp4C;
    s32 phi_v0;
    enum sfx_e phi_a0;
    f32 temp_f0;
    s32 sp3C;
    s32 sp38;
    f32 sp34;
#ifdef WARP_CAULDRON_MENU
    s32 face_buttons[3];
    s32 side_buttons[3];
    f32 joystick[2];
    f32 delta_time;
#endif
    
    lair_func_8038A864(this);
    if (!this->volatile_initialized) {
        sp50 = FALSE;
        this->volatile_initialized = TRUE;
        this->marker->propPtr->unk8_3 = TRUE;
        this->unk1C[1] = 0.0f;
        this->velocity[0] = this->yaw;
        if (this->modelCacheIndex == ACTOR_2DB_DINGPOT) {
            if (fileProgressFlag_get(FILEPROG_F3_MET_DINGPOT)) {
                sp4C = (fileProgressFlag_get(FILEPROG_CF_HAS_ENTERED_FINAL_FIGHT)) ? 0xFB7 : 0xFAE;
                phi_v0 = (fileProgressFlag_get(FILEPROG_CF_HAS_ENTERED_FINAL_FIGHT)) ? 0xFBC : 0xFB7;
                this->lifetime_value = 35.0f;
                this->unk38_31 = randi2(0, phi_v0 - sp4C);
            }
            this->scale = 1.8f;
            subaddie_set_state_with_direction(this, 6, 0.99f, 1);
            func_802D09B8(this, 2);
        }
        if (fileProgressFlag_get(chWarpCauldron_getFileProgressFlagIndex(this))) {
#ifdef WARP_CAULDRON_MENU
 #ifdef OPTIONS_MENU
            bool completedCauldronSetFlagCheck = (is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU))
                                                 ? (count_total_active_cauldrons() > 1) : fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this));
 #else
            bool completedCauldronSetFlagCheck = (count_total_active_cauldrons() > 1);
 #endif
#endif
            func_8038A704(this);
            func_802D09B8(this, 2);
            func_8038A96C(this, 2);
            sp50 = TRUE;
            if( ( func_802D677C(-1) != 0 
                  && (func_802D677C(-1) == D_80393620[this->actorTypeSpecificField - 1].unk0) 
                  && (func_802D67AC(-1) == MAP_16_GV_RUBEES_CHAMBER) 
                  && (func_802D680C(-1) == this->actorTypeSpecificField)
                ) 
                || (gsworld_getExit() == D_80393620[this->actorTypeSpecificField - 1].unk2)
            ) {
                func_8028F85C(this->position);
                this->unk10_12 = 1;
                func_8038AB90(this, 5, 1, 0, 0.0f);
            }
/*
 * This code is used for the Cauldron Cutscenes activated from the Warp Menu.
 * If the Cauldron is needed in a Cauldron Cutscene, then set it up properly and place Banjo inside it.
 * When it returns back to the original Cauldron, reopen the Warp Menu and reset some values.
 */
#ifdef WARP_CAULDRON_MENU
              else if (get_inWarpCauldronCutscene()
                       && ((currCauldronID == this->actorTypeSpecificField) || (targetCauldronID == this->actorTypeSpecificField))) {
                if (get_inWarpCauldronCutscene() == 2) {
                    func_8028F85C(this->position);
                    this->unk38_0 = TRUE;
                    func_8038AB90(this, 9, 0, 0, 0.0f);
                    actor_loopAnimation(this);
                }
                if (currCauldronID == this->actorTypeSpecificField) {
                    if (get_inWarpCauldronCutscene() == 2) {
                        reopen_warpMenu_zoomboxes(chWarpCauldron_getFileProgressFlagIndex(this));
                    } else if (get_inWarpCauldronCutscene() == 1) {
                        currCauldronID = 0;
                    }
                    targetCauldronID = 0;
                    skipUnderwaterCheck = TRUE;
                    set_inWarpCauldronCutscene(0);
                }
            }
#endif
            if (!fileProgressFlag_get(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET) 
#ifdef WARP_CAULDRON_MENU
                && completedCauldronSetFlagCheck
#else
                && fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this))
#endif
                ) {
                if (func_802D677C(-1) != gsworld_getMap()) {
                    gcdialog_showDialog(ASSET_F7A_DIALOG_UNKNOWN, 4, NULL, NULL, NULL, NULL);
                    fileProgressFlag_set(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET, 1);
                }
            }
        }
        if (sp50 == 0) {
            this->unk10_12 = 0;
            func_8038A96C(this, 0);
        }
/*
 * When the Health Bar is less than or equal to 2 Honeycombs, it's supposed to be forced to display on screen.
 * However, when warping between Cauldrons, it doesn't display like it should when you warp to your destination.
 * It seems that there is a value the game checks to determine whether to force the Health Bar to display that is supposed to be set to 0,
 * but going through a Cauldron Warp doesn't reset it properly.
 * This fixes the issue by resetting that value when the Cauldron is initialized and whenever VOLATILE_FLAG_1E is set, which is only during Cauldron Warps.
 */
#if defined(BUG_AND_OVERSIGHT_FIXES) || defined(WARP_CAULDRON_MENU)
        if (volatileFlag_get(VOLATILE_FLAG_1E)
 #ifdef OPTIONS_MENU
            && (is_qol_feature_enabled(QOL_ID_BUG_AND_OVERSIGHT_FIXES) || is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU))
 #endif
            ) {
            func_80347A70();
        }
#endif
    }

#ifdef WARP_CAULDRON_MENU
    check_if_currCauldron_is_underwater(this);
#endif

    switch(this->state){
        case 1: //L8038B0F4
            if (func_8038A690(this)) {
                func_8028F918(2);
                subaddie_set_state_forward(this, 2);
                this->unk38_0 = FALSE;
                func_8038A96C(this, 1);
                gcStaticCamera_activate(D_80393620[this->actorTypeSpecificField - 1].unk3);
                func_802D09B8(this, 2);
#ifdef WARP_CAULDRON_MENU
 #ifdef OPTIONS_MENU
                if (is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU)) {
                    warpCauldron_state_1_qol_funcs(this, phi_a0);
                } else {
                    warpCauldron_state_1_vanilla_funcs(this, phi_a0);
                }
 #else
                warpCauldron_state_1_qol_funcs(this, phi_a0);
 #endif
#else
                phi_a0 = (fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this)) != 0) ? SFX_107_CAULDRON_ACTIVATION_1 : SFX_108_CAULDRON_ACTIVATION_2;
                gcsfx_playAtSampleRate(phi_a0, 32000);
                if (!fileProgressFlag_get(FILEPROG_F5_COMPLETED_A_WARP_CAULDRON_SET) && !fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this))) {
                    gcdialog_showDialog(ASSET_F79_DIALOG_UNKNOWN, 4, NULL, NULL, NULL, NULL);
                }
                if (fileProgressFlag_get(chWarpCauldron_getPairedFileProgressFlagIndex(this))){
                    switch(this->actorTypeSpecificField){
                        case 2://L8038B204
                            func_802D6310(2.0f, MAP_6A_GL_TTC_AND_CC_PUZZLE, 0x62, 0x22, 0);
                            break;

                        case 1://L8038B228 
                            func_802D6310(2.0f, MAP_6F_GL_FP_LOBBY, 0x63, 0x23, 0);
                            break;

                        case 4://L8038B24C
                            func_802D6310(2.0f, MAP_6F_GL_FP_LOBBY, 0x64, 0x24, 0);
                            break;

                        case 3://L8038B270
                            func_802D6310(2.0f, MAP_77_GL_RBB_LOBBY, 0x65, 0x25, 0);
                            break;

                        case 6://L8038B294
                            func_802D6310(2.0f, MAP_6C_GL_RED_CAULDRON_ROOM, 0x66, 0x26, 0);
                            break;

                        case 5://L8038B2B8
                            func_802D6310(2.0f, MAP_79_GL_CCW_LOBBY, 0x67, 0x27, 0);
                            break;

                        case 10://L8038B2DC
                            func_802D6310(2.0f, MAP_8E_GL_FURNACE_FUN, 0x8C, 0x29, 0);
                            break;

                        case 9://L8038B300
                            func_802D6310(2.0f, MAP_93_GL_DINGPOT, 0x8D, 0x2A, 0);
                            break;
                    }
                }
#endif
            }
            break;

        case 2: //L8038B324
            temp_f0 = anctrl_getAnimTimer(this->anctrl);
            for(sp3C = 0; D_803936E4[sp3C] < temp_f0; sp3C++)
                ;
            
            this->unk38_0 = BOOL(sp3C & 1);
            if (actor_animationIsAt(this, 0.95f)) {
                func_8038A704(this);
// Moved this into warpCauldron_state_1_qol_funcs.
#ifndef WARP_CAULDRON_MENU
                fileProgressFlag_set(chWarpCauldron_getFileProgressFlagIndex(this), 1);
#elif defined(OPTIONS_MENU)
                if (!is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU)) {
                    fileProgressFlag_set(chWarpCauldron_getFileProgressFlagIndex(this), 1);
                }
#endif
                func_8028F918(0);
                this->unk1C[2] = 4.0f;
            }
            break;

        case 3: //L8038B3DC
            this->unk38_0 = TRUE;
            if (this->unk1C[2] != 0.0f) {
                this->unk1C[2] = this->unk1C[2] - 1.0f;
            } else {
                func_8038AB90(this, 5, 1, 0, 0.0f);
#ifdef WARP_CAULDRON_MENU
 #ifdef OPTIONS_MENU
                if (is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU)) {
                    func_8038AB90(this, 8, 2, SFX_7C_CHEBOOF, 0.0f);
                } else {
                    func_8038AB90(this, 4, 2, SFX_A6_MAGICAL_FINISH, 2.6f);
                }
 #else
                func_8038AB90(this, 8, 2, SFX_7C_CHEBOOF, 0.0f);
 #endif
#else
                func_8038AB90(this, 4, 2, SFX_A6_MAGICAL_FINISH, 2.6f);
#endif
            }
            func_8038A96C(this, 3);
            break;

        case 7: //L8038B460
            this->unk38_0 = TRUE;
            if (actor_animationIsAt(this, 0.62f)) {
                func_8030E6D4(SFX_1B_EXPLOSION_1);
            }
        case 5: //L8038B48C
            func_8038A96C(this, 3);
            if (actor_animationIsAt(this, 0.01f)) {
                gcsfx_play(SFX_7C_CHEBOOF);
            }
            if (actor_animationIsAt(this, 0.63f)) {
                volatileFlag_set(VOLATILE_FLAG_1E, 0);
                func_802D677C(0);
                func_8028FCAC();
/*
 * If you're about to exit from the Yellow Warp Cauldron in FF and you haven't seen the Enter Furnace Fun Cutscene,
 * then switch the landing spot from in front of the Cauldron to the middle of the Tooty Warp Pad.
 * 
 * NOTE: This is only possible if you have WARP_CAULDRON_MENU enabled and entered the VOLATILE_FLAG_15_SANDCASTLE_UNLOCK_ALL_CAULDRONS cheat code with ADDITIONAL_CHEATS enabled.
 */
#if defined(WARP_CAULDRON_MENU) && defined(ADDITIONAL_CHEATS)
                if ((gsworld_getMap() == MAP_8E_GL_FURNACE_FUN) && !fileProgressFlag_get(FILEPROG_F4_ENTER_FF_CUTSCENE)) {
                    f32 updatedPlayerPos[3] = this->position;
                    // The object with the Actor ID of 0x242 is the one that warps the player into and out of Furnace Fun.
                    nodeprop_getPosition(nodeprop_findByActorIdAndActorPosition(0x242, this), sp54);

                    // Raise the Player's position so Banjo can land in the middle of the Warp Pad.
                    updatedPlayerPos[1] += 50.0f;
                    func_8028F85C(updatedPlayerPos);
                } else {
                    nodeprop_getPosition(nodeprop_findByActorIdAndActorPosition(D_80393620[this->actorTypeSpecificField - 1].unk6, this), sp54);
                }
#else
                nodeprop_getPosition(nodeprop_findByActorIdAndActorPosition(D_80393620[this->actorTypeSpecificField - 1].unk6, this), sp54);
#endif
                if (this->actorTypeSpecificField == 7) {
                    func_8028F66C(BS_INTR_36_DINGPOT);
                    gcStaticCamera_activate(0x82);
                } else {
                    func_8028F4B8(sp54, 1620.0f, -4100.0f);
                }
            }
            if (actor_animationIsAt(this, 0.98f)) {
                func_8038A704(this);
                actor_loopAnimation(this);
#ifdef WARP_CAULDRON_MENU
                currCauldronID = 0;
                currCauldronUnderwater = FALSE;
#endif
            }
            break;

        case 4: //L8038B584
            func_8038A96C(this, 3);
            if (actor_animationIsAt(this, 0.99f)) {
#ifdef WARP_CAULDRON_MENU
 #ifdef OPTIONS_MENU
                u8 warpLocationIndex = (is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU)) ? get_original_cauldron_order_index(scrollingMenu.selection) : ((this->actorTypeSpecificField - 1) ^ 1);
                if (is_qol_feature_enabled(QOL_ID_WARP_CAULDRON_MENU))
                    stop_all_timers();
 #else
                u8 warpLocationIndex = get_original_cauldron_order_index(scrollingMenu.selection);
                stop_all_timers();
 #endif

                currCauldronID = 0;
                currCauldronUnderwater = FALSE;
#endif
                func_802D6344();
#ifdef WARP_CAULDRON_MENU
                func_802D677C(D_80393620[warpLocationIndex].unk0);
                func_802D67AC(0x16);
                func_802D680C(warpLocationIndex + 1);
                func_802D683C(D_80393620[warpLocationIndex].unk1);
                func_8031CC40(D_80393620[warpLocationIndex].unk0, D_80393620[warpLocationIndex].unk2);
#else
                func_802D677C(D_80393620[((this->actorTypeSpecificField - 1) ^ 1)].unk0);
                func_802D67AC(0x16);
                func_802D680C(((this->actorTypeSpecificField - 1) ^ 1) + 1);
                func_802D683C(D_80393620[((this->actorTypeSpecificField - 1) ^ 1)].unk1);
                func_8031CC40(D_80393620[((this->actorTypeSpecificField - 1) ^ 1)].unk0, D_80393620[((this->actorTypeSpecificField - 1) ^ 1)].unk2);
#endif
            }
            break;

        case 6: //L8038B64C
            if (func_8038A690(this) && !fileProgressFlag_get(FILEPROG_F3_MET_DINGPOT)) {
                gcdialog_showDialog(ASSET_FAD_DIALOG_DINGPOT_MEET, 0xA, this->position, NULL, __chWarpCauldron_dingpotDialogCallback, NULL);
            }
            this->unk38_0 = TRUE;

            sp3C = 0;
            if (fileProgressFlag_get(FILEPROG_FC_DEFEAT_GRUNTY)){
                if(jiggyscore_total() == 100){
                    sp3C = 1;
                }
            }
            else{ 
                sp3C = 1;
            }
            if (sp3C != 0) {
                func_8038AB90(this, 7, 1, 0, 0.0f);
            }
            func_8038AC7C(this);
            sp38 = subaddie_getYawToPlayer(this);
            if( lair_func_8038ADF0(sp38, (s32) this->velocity[0]) 
                || lair_func_8038ADF0((s32) this->velocity[0], sp38)
            ) {
                this->yaw_ideal = (f32) sp38;
            }
            subaddie_turnToYaw(this, 3.0f);
            if( actor_animationIsAt(this, 0.114f)
                || actor_animationIsAt(this, 0.217f)
                || actor_animationIsAt(this, 0.321f)
            ) {
                sp34 = randf2(0.85f, 0.95f);
                func_8030E878(SFX_20_METAL_CLANK_1, sp34, 16000, this->position, 100.0f, 1750.0f);
            }
            if( actor_animationIsAt(this, 0.49f)
                || actor_animationIsAt(this, 0.68f)
            ) {
                sp34 = randf2(0.65f, 0.75f);
                func_8030E878(SFX_F9_GRUNTLING_NOISE_1, sp34, 16000, this->position, 100.0f, 1750.0f);
            }
            break;

#ifdef WARP_CAULDRON_MENU
        case 8:
            if (actor_animationIsAt(this, 0.01f)) {
                set_warpMenuActive(TRUE);
                close_hud_and_dialog();
                currCauldronID = this->actorTypeSpecificField;
                open_warpMenu_zoomboxes(chWarpCauldron_getFileProgressFlagIndex(this));
            }
            if (actor_animationIsAt(this, 0.37f)) {
                close_hud_and_dialog();
            }
            if (actor_animationIsAt(this, 0.98f)) {
                subaddie_set_state_with_direction(this, 9, 0.99f, 1);
                actor_loopAnimation(this);
            }

        case 9:
            delta_time = time_getDelta();
            controller_copyFaceButtons(0, face_buttons);
            controller_copySideButtons(0, side_buttons);
            controller_getJoystick(0, joystick);
            
            if (get_inWarpCauldronCutscene()) {
                break;
            } else if (scrollingMenu.menuFinishedDisplaying) {
                if (scrollingMenu.moveDelay > 0) {
                    scrollingMenu.moveDelay--;

                    if (scrollingMenu.moveDelay == 5) {
                        update_warpMenu_zoombox_data(chWarpCauldron_getFileProgressFlagIndex(this));
                        update_scrollingMenu_zoombox_highlights();
                    }

                    if (scrollingMenu.movingMenu) {
                        u8 i;
                        for (i = 0; i < 6; i++) {
                            if (scrollingMenu.zoombox[i]) {
                                update_scrollingMenu_zoombox_y_pos(i);

                                if ((i == 0) || (i == 5)) {
                                    update_scrollingMenu_zoombox_transparency(i);
                                }
                            }
                        }
                    }
                } else if (scrollingMenu.selectDelay > 25) {
                    scrollingMenu.selectDelay--;
                    reset_scrollingMenu_zoombox_y_pos_and_transparency();
 #ifdef DPAD_FUNCTIONALITY
                } else if ((0.75 < joystick[JOYSTICK_Y])
                           || pfsManager_dpad_buttons_valid(BUTTON_D_UP, TRUE)) {
 #else
                } else if (0.75 < joystick[JOYSTICK_Y]) {
 #endif
                    reset_scrollingMenu_zoombox_y_pos_and_transparency();

                    if (cauldronZoomboxData[(s32) scrollingMenu.selection].id != (enum file_progress_e)find_first_available_cauldron_flag(chWarpCauldron_getFileProgressFlagIndex(this), 0, 1, TRUE)) {
                        do {
                            scrollingMenu.selection--;
                        } while (!fileProgressFlag_get(cauldronZoomboxData[(s32) scrollingMenu.selection].id)
                                 || (chWarpCauldron_getFileProgressFlagIndex(this) == cauldronZoomboxData[(s32) scrollingMenu.selection].id));
                        scrollingMenu.menuMoveDirection = -1;

                        update_scrollingMenu_info();
                            
                        scrollingMenu.moveDelay = 6;
                    }
 #ifdef DPAD_FUNCTIONALITY
                } else if ((joystick[JOYSTICK_Y] < -0.75)
                           || pfsManager_dpad_buttons_valid(BUTTON_D_DOWN, TRUE)) {
 #else
                } else if (joystick[JOYSTICK_Y] < -0.75) {
 #endif
                    reset_scrollingMenu_zoombox_y_pos_and_transparency();

                    if (cauldronZoomboxData[(s32) scrollingMenu.selection].id != (enum file_progress_e)find_first_available_cauldron_flag(chWarpCauldron_getFileProgressFlagIndex(this), 9, -1, TRUE)) {
                        do {
                            scrollingMenu.selection++;
                        } while (!fileProgressFlag_get(cauldronZoomboxData[(s32) scrollingMenu.selection].id)
                                 || (chWarpCauldron_getFileProgressFlagIndex(this) == cauldronZoomboxData[(s32) scrollingMenu.selection].id));
                        scrollingMenu.menuMoveDirection = 1;

                        update_scrollingMenu_info();
                            
                        scrollingMenu.moveDelay = 6;
                    }
                } else {
                    reset_scrollingMenu_zoombox_y_pos_and_transparency();
                }

                if (scrollingMenu.selectDelay > 25) {
                    
                } else if ((face_buttons[FACE_BUTTON(BUTTON_A)] == 1) && (scrollingMenu.moveDelay < 6)) {
                    scrollingMenu.bottomPortraitOpacityFix = FALSE;
                    close_scrollingMenu_zoomboxes();
                    this->unk10_12 = 2;
                    timedFunc_set_1(0.8f, (GenFunction_1) warpMenu_made_selection, 2);
                } else if (face_buttons[FACE_BUTTON(BUTTON_B)] == 1) {
                    scrollingMenu.bottomPortraitOpacityFix = FALSE;
                    close_scrollingMenu_zoomboxes();
                    this->unk10_12 = 1;
                    timedFunc_set_1(0.8f, (GenFunction_1) warpMenu_made_selection, 1);
                } else if (scrollingMenu.selectDelay > 0) {
                    scrollingMenu.selectDelay--;
                } else if ((side_buttons[SIDE_BUTTON(BUTTON_L)] == 1) && ((1.0f < scrollingMenu.menuCycleInstructionsTimer) || scrollingMenu.textResetOnce) && (scrollingMenu.moveDelay < 1)) {
                    scrollingMenu.selectDelay = 30;
                    scrollingMenu.textResetOnce = FALSE;
                    warp_cauldron_cutscene(this->actorTypeSpecificField, scrollingMenu.selection, TRUE, 0.0f);
                }

                scrollingMenu.menuCycleInstructionsTimer += delta_time;
                if (20.0f < scrollingMenu.menuCycleInstructionsTimer) {
                    func_8031877C(scrollingMenu.topZoombox);
                    gczoombox_setStrings(scrollingMenu.topZoombox, 4, (char **)&scrollingMenu.instructions);
                    scrollingMenu.menuCycleInstructionsTimer = 0.0f;
                    scrollingMenu.textResetOnce = TRUE;
                }
            /*
             * Small issue where gczoombox_draw will try to increase the value of 'unk168' when the zoombox opens, which raises the opacity of the portrait.
             * This is a quick and easy fix to keep very bottom zoombox portrait invisible when the warp menu opens.
             */
            } else if (scrollingMenu.bottomPortraitOpacityFix) {
                scrollingMenu.zoombox[5]->unk168 = 0x00;
            }

            /*
             * Would've rather done this completely differently, but there are some issues with the Yellow Cauldrons not updating their state
             * properly when passing the actors through "timedFunc_set".
             */
            if (warpCheck == 2) {
                func_8038AB90(this, 4, 2, SFX_A6_MAGICAL_FINISH, 2.6f);
                warpCheck = 0;
            } else if (warpCheck == 1) {
                func_8038AB90(this, 5, 1, 0, 0.0f);
                warpCheck = 0;
            }
            break;
            
#endif
    }//L8038B854
    
    this->unk1C[1] = (f32)this->marker->unk14_21;
}

Actor *chWarpCauldron_draw(ActorMarker *marker, Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    Actor *this;
    s32 sp3C[4];

    this = marker_getActor(marker);
    if(this->modelCacheIndex == ACTOR_23B_WARP_CAULDRON) {
        func_8033A45C(3, BOOL(this->unk38_0));
        func_8033A45C(4, this->unk38_0 ? FALSE : TRUE);
    }
    this = actor_draw(marker, gfx, mtx, vtx);
    if (marker->unk14_21 && this->unk38_0 && (getGameMode() != GAME_MODE_4_PAUSED)) {
        sp3C[1] = randi2(200, 255);
        sp3C[0] = randi2(150, sp3C[1]);
        sp3C[2] = 0;
        sp3C[3] = randi2(40, 80);
        if (globalTimer_getTime() & 1) {
            func_802EE354(this, 0x3E9, 5, randi2(-10, 90), randf2(0.3f, 0.7f), 0.28f, 0.45f, sp3C, 5, 0);
        }
    }
    return this;
}

#ifdef WARP_CAULDRON_MENU
void warpMenu_init(enum file_progress_e currFlag) {
    int i = code94620_func_8031B5B0();

    scrollingMenu.onScreenSelection = scrollingMenu.selectDelay = 0;
    scrollingMenu.selection = (u8)find_first_available_cauldron_flag(currFlag, 0, 1, FALSE);
    scrollingMenu.menuMoveDirection = 1;
    scrollingMenu.moveDelay = -1;
    scrollingMenu.onLowerHalfOfMenu = scrollingMenu.movingMenu = scrollingMenu.menuFinishedDisplaying = scrollingMenu.textResetOnce = scrollingMenu.bottomPortraitOpacityFix = FALSE;
    scrollingMenu.menuCycleInstructionsTimer = 0.0f;
    if (scrollingMenu.topZoombox) {
        gczoombox_free(scrollingMenu.topZoombox);
        scrollingMenu.topZoombox = NULL;
    }
    scrollingMenu.instructions.one = (&WARP_GENERAL_INSTRUCTIONS)[i];
    scrollingMenu.instructions.two = (&WARP_INSTRUCTIONS_A_BUTTON)[i];
    scrollingMenu.instructions.three = (&WARP_INSTRUCTIONS_L_BUTTON)[i];
    scrollingMenu.instructions.four = (&WARP_INSTRUCTIONS_B_BUTTON)[i];
    for (i = 0; i < 6; i++) {
        if (scrollingMenu.zoombox[i]) {
            gczoombox_free(scrollingMenu.zoombox[i]);
            scrollingMenu.zoombox[i] = NULL;
        }
    }
}

void warpMenu_zoombox_callback(s32 portrait_id, s32 zoombox_state) {
    u8 i;
    
    if (zoombox_state == 2) {
        for (i = 1; i < 6; i++) {
            if (scrollingMenu.zoombox[i]) {
                gczoombox_highlight(scrollingMenu.zoombox[i], FALSE);
            }
        }
    }
}

void update_warpMenu_colors(u8 selectionIndex, u8 zoomboxIndex) {
 #ifdef GENERIC_CAULDRON_NAMES
    scrollingMenu.zoombox[zoomboxIndex]->portraitRGB[0] = (u8)(D_803935A8[get_original_cauldron_order_index(selectionIndex) / 2][1][0] * 255.0f);
    scrollingMenu.zoombox[zoomboxIndex]->portraitRGB[1] = (u8)(D_803935A8[get_original_cauldron_order_index(selectionIndex) / 2][1][1] * 255.0f);
    scrollingMenu.zoombox[zoomboxIndex]->portraitRGB[2] = (u8)(D_803935A8[get_original_cauldron_order_index(selectionIndex) / 2][1][2] * 255.0f);
 #endif
    scrollingMenu.zoombox[zoomboxIndex]->textRGB[0] = cauldronTextColors[get_original_cauldron_order_index(selectionIndex) / 2][0];
    scrollingMenu.zoombox[zoomboxIndex]->textRGB[1] = cauldronTextColors[get_original_cauldron_order_index(selectionIndex) / 2][1];
    scrollingMenu.zoombox[zoomboxIndex]->textRGB[2] = cauldronTextColors[get_original_cauldron_order_index(selectionIndex) / 2][2];
}

void update_warpMenu_zoombox_strings(u8 selectionIndex, u8 zoomboxIndex, bool instantlyPrintStrings) {
    u8 *zoombox_strings[2];
    static u8 upperTextLine[6][0x20];
    static u8 lowerTextLine[6][0x20];
    bool onlyOneString = strcmp("", cauldronZoomboxData[selectionIndex].secondStr);

    strcpy(upperTextLine[zoomboxIndex], "");
    strcat(upperTextLine[zoomboxIndex], cauldronZoomboxData[selectionIndex].firstStr);
    strcpy(lowerTextLine[zoomboxIndex], "");
    strcat(lowerTextLine[zoomboxIndex], cauldronZoomboxData[selectionIndex].secondStr);

    if (onlyOneString) {
        scrollingMenu.zoombox[zoomboxIndex]->textYOffset = -1;
    } else {
        scrollingMenu.zoombox[zoomboxIndex]->textYOffset = 4;
    }

    zoombox_strings[0] = upperTextLine[zoomboxIndex];
    zoombox_strings[1] = lowerTextLine[zoomboxIndex];

    gczoombox_setStrings(scrollingMenu.zoombox[zoomboxIndex], 2, zoombox_strings);
    update_warpMenu_colors(selectionIndex, zoomboxIndex);

    if (instantlyPrintStrings) {
        do {
            gczoombox_update(scrollingMenu.zoombox[zoomboxIndex]);
        } while (scrollingMenu.zoombox[zoomboxIndex]->state != 0xA);
    }
}

void open_warpMenu_zoomboxes(enum file_progress_e currFlag) {
    u8 i;
    u8 j = 0;

    warpMenu_init(currFlag);
    
    scrollingMenu.topZoombox = gczoombox_new(0xA, ZOOMBOX_SPRITE_56_WARP_CAULDRON, 2, 0, NULL);
    gczoombox_setStrings(scrollingMenu.topZoombox, 4, (char **)&scrollingMenu.instructions);
    gczoombox_open(scrollingMenu.topZoombox);
    gczoombox_maximize(scrollingMenu.topZoombox);
 #ifdef GENERIC_CAULDRON_NAMES
    scrollingMenu.topZoombox->portraitRGB[0] = (u8)(D_803935A8[(((s32)currFlag - 0x49)>>1)][1][0] * 255.0f);
    scrollingMenu.topZoombox->portraitRGB[1] = (u8)(D_803935A8[(((s32)currFlag - 0x49)>>1)][1][1] * 255.0f);
    scrollingMenu.topZoombox->portraitRGB[2] = (u8)(D_803935A8[(((s32)currFlag - 0x49)>>1)][1][2] * 255.0f);
 #endif

    for (i = 0; i < 6; i++) {
        f32 delay = ((f32)(MIN(i, 4)) / 10.0f) + 0.1f;

        while (j < 10) {
            if (fileProgressFlag_get(cauldronZoomboxData[j].id) && (cauldronZoomboxData[j].id != currFlag)) {
                break;
            }
            j++;
        }
        if (j == 10) {
            break;
        }

        scrollingMenu.zoombox[i] = gczoombox_new((30 * i + 54), cauldronZoomboxData[j].portrait, 2, 0, warpMenu_zoombox_callback);
        gczoombox_func_803184C8(scrollingMenu.zoombox[i], 60.0f, 5, 2, 0.3f, 0, 0);
        func_80318640(scrollingMenu.zoombox[i], 0x40, 0.75f, 0.99999f, 0);
        if (i != 5) {
            func_80318760(scrollingMenu.zoombox[i], 8000);
        } else {
            func_80318760(scrollingMenu.zoombox[i], 0);
            scrollingMenu.zoombox[i]->zoomboxAlpha = scrollingMenu.zoombox[i]->textAlpha = 0x00;
            scrollingMenu.bottomPortraitOpacityFix = TRUE;
        }
        
        update_warpMenu_zoombox_strings(j, i, FALSE);
        
        timedFunc_set_1(delay, (GenFunction_1) gczoombox_open, (s32)scrollingMenu.zoombox[i]);
        timedFunc_set_1(delay, (GenFunction_1) gczoombox_maximize, (s32)scrollingMenu.zoombox[i]);

        j++;
    }

    timedFunc_set_1(31.0f * time_getDelta(), (GenFunction_1) set_menu_finished_displaying_state, TRUE);
}

void update_warpMenu_zoombox_data(enum file_progress_e currFlag) {
    if (scrollingMenu.movingMenu) {
        s8 i;
        s8 firstIndex;
        s8 lastIndex;
        u8 selectionIndex;
        if (!scrollingMenu.onLowerHalfOfMenu) {
            firstIndex = 0;
            lastIndex = 6;
            selectionIndex = scrollingMenu.selection - scrollingMenu.onScreenSelection;
        } else {
            firstIndex = 5;
            lastIndex = -1;
            selectionIndex = scrollingMenu.selection - (5 - scrollingMenu.onScreenSelection - (u8)scrollingMenu.onLowerHalfOfMenu);
        }
        for (i = firstIndex; i != lastIndex; i -= scrollingMenu.menuMoveDirection) {
            if (scrollingMenu.zoombox[i]) {
                func_8031877C(scrollingMenu.zoombox[i]);
                update_warpMenu_zoombox_strings(selectionIndex, i, TRUE);
                zoombox_setSprite(scrollingMenu.zoombox[i], cauldronZoomboxData[selectionIndex].portrait);
                selectionIndex = find_first_available_cauldron_flag(currFlag, (selectionIndex - scrollingMenu.menuMoveDirection), -scrollingMenu.menuMoveDirection, FALSE);
            }
        }
    }
}

/*
 * The game seems to crash under very specific circumstances if it transitions to a map with too many zoomboxes active.
 * To prevent this during a Warp Cauldron Cutscene when the Warp Menu is open, free most of the zoomboxes, then instantly reopen new zoomboxes when the cutscene is over.
 */
void warpMenu_zoomboxFree(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        if (scrollingMenu.zoombox[i]) {
            gczoombox_free(scrollingMenu.zoombox[i]);
            scrollingMenu.zoombox[i] = NULL;
        }
    }
}

void reopen_warpMenu_zoomboxes(enum file_progress_e currFlag) {
    u8 i = scrollingMenu.onScreenSelection + (u8)scrollingMenu.onLowerHalfOfMenu;
    u8 j = scrollingMenu.selection;

    while (i > 0) {
        j = find_first_available_cauldron_flag(currFlag, (j - 1), -1, FALSE);
        i--;
    }
    for (i = 0; i < 6; i++) {
        while (j < 10) {
            if (fileProgressFlag_get(cauldronZoomboxData[j].id) && (cauldronZoomboxData[j].id != currFlag)) {
                break;
            }
            j++;
        }
        if (j == 10) {
            break;
        }

        scrollingMenu.zoombox[i] = gczoombox_new((30 * i + 24 + ((u8)(!scrollingMenu.onLowerHalfOfMenu) * 30)), cauldronZoomboxData[j].portrait, 2, 0, NULL);
        gczoombox_func_803184C8(scrollingMenu.zoombox[i], 60.0f, 5, 2, 0.3f, 0, 0);
        func_80318640(scrollingMenu.zoombox[i], 0x40, 0.75f, 0.99999f, 0);
        func_80318760(scrollingMenu.zoombox[i], 0);
        gczoombox_open(scrollingMenu.zoombox[i]);
        gczoombox_maximize(scrollingMenu.zoombox[i]);
        update_warpMenu_zoombox_strings(j, i, TRUE);
        if (j != scrollingMenu.selection) {
            gczoombox_highlight(scrollingMenu.zoombox[i], FALSE);
            scrollingMenu.zoombox[i]->unk168 = 0x80;
        }

        j++;
    }
    if (!scrollingMenu.onLowerHalfOfMenu) {
        if (scrollingMenu.zoombox[5]) {
            scrollingMenu.zoombox[5]->unk168 = scrollingMenu.zoombox[5]->zoomboxAlpha = scrollingMenu.zoombox[5]->textAlpha = 0x00;
        }
    } else {
        if (scrollingMenu.zoombox[0]) {
            scrollingMenu.zoombox[0]->unk168 = scrollingMenu.zoombox[0]->zoomboxAlpha = scrollingMenu.zoombox[0]->textAlpha = 0x00;
        }
    }
}
#endif
