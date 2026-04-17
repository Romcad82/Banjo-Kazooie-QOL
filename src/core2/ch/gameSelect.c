#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "gameSelect.h"

#include "core2/modelRender.h"

#include "../gc/zoombox.h"
#include "../code_C9E70.h"

#include "config.h"

#ifndef ABS
#define	ABS(d)		((d) >= 0) ? (d) : -(d)
#endif

void debugScoreStates(void);
void clearScoreStates(void);

Actor *gameSelect_draw(ActorMarker *, Gfx **, Mtx **, Vtx **);
Actor *gameSelect_zoomboxDraw(ActorMarker *, Gfx **, Mtx **, Vtx **);
void gameSelect_update(Actor *this);
void gameSelect_initAndUpdate(Actor *this);

extern void func_802C71F0(Actor *);
extern void func_802C74F4(Actor *, s32, f32 );
extern void warp_lairEnterLairFromSMLevel(s32, s32);
extern void warp_smExitBanjosHouse(s32, s32);
extern void controller_getJoystick(s32, f32*);
#ifdef OPTIONS_MENU
extern void set_menu_finished_displaying_state(bool setState);
#endif

extern char *gcpausemenu_TimeToA(int);
extern struct5Bs *func_803097A0(void);

/* .data */
f32 INITIAL_CAMERA_POSITIONS[3][3] = {
    { -320.0f, 340.0f, 350.0f },
    { 110.0f, 340.0f, 110.0f },
    { -413.333313f, 353.333313f, -234.305511f }
};

#ifdef OPTIONS_MENU
// IDs must be in the same order as they are in enums.h, except for QOL_ID_NONE.
static const scrollingMenuZoomboxFormat optionsZoomboxData[] = {
 #ifdef NOTE_SAVING
    {QOL_ID_NOTE_SAVING,                            "NOTE SAVING: ",          "",                 ZOOMBOX_SPRITE_8_MUSIC_NOTE_1,
     "MUSIC NOTES BECOME A PERMANENT COLLECTIBLE. THEY WON'T RESPAWN WHEN YOU DIE OR LEAVE THE LEVEL."},
 #endif
 #ifdef JINJO_SAVING
    {QOL_ID_JINJO_SAVING,                           "JINJO SAVING: ",         "",                 ZOOMBOX_SPRITE_22_JINJO_BLUE,
     "JINJOS BECOME A PERMANENT COLLECTIBLE. THEY WON'T RESPAWN WHEN YOU DIE OR LEAVE THE LEVEL."},
 #endif
 #ifdef HEALTH_SYSTEM_REWORK
    {QOL_ID_HEALTH_SYSTEM_REWORK,                   "HEALTH SYSTEM",          "REWORK: ",         ZOOMBOX_SPRITE_2C_HONEYCOMB,
     "LETS YOU ADD A 9TH HONEYCOMB TO THE HEALTH BAR. ALSO CHANGES HOW DOUBLE HEALTH WORKS. INSTEAD OF GIVING THE PLAYER MAXIMUM HEALTH, IT SIMPLY DOUBLES YOUR CURRENT HEALTH TOTAL."},
 #endif
 #ifdef WARP_CAULDRON_MENU
    {QOL_ID_WARP_CAULDRON_MENU,                     "WARP CAULDRON",          "MENU: ",           ZOOMBOX_SPRITE_56_WARP_CAULDRON,
     "ADDS A MENU TO THE WARP CAULDRONS, LETTING YOU WARP TO ANY CAULDRON YOU WANT."},
 #endif
 #if defined(BUG_AND_OVERSIGHT_FIXES) || defined(VANILLA_SPECIFIC_BUG_AND_OVERSIGHT_FIXES)
    {QOL_ID_BUG_AND_OVERSIGHT_FIXES,                "BUG FIXES: ",            "",                 ZOOMBOX_SPRITE_34_TERMITE,
     "FIXES MANY BUGS AND ISSUES THROUGHOUT THE GAME."},
 #endif
 #ifdef BETTER_CAMERA
    {QOL_ID_BETTER_CAMERA,                          "BETTER CAMERA: ",        "",                 ZOOMBOX_SPRITE_F_BOTTLES,
     "THE CAMERA IS SLIGHTLY BETTER. IT DOESN'T DRASTICALLY CHANGE ANGLES WHEN ROTATING AROUND LEVEL GEOMETRY."},
 #endif
 #ifdef IGNORE_FRAMERATE_ALTERING_OBJECTS
    {QOL_ID_IGNORE_FRAMERATE_ALTERING_OBJECTS,      "DEFAULT TO 30 FPS: ",    "",                 ZOOMBOX_SPRITE_47_MUMMUM,
     "SOME ROOMS AND CUTSCENES SET THE FPS TO 20 INSTEAD OF 30. CHANGE IT SO ALL ROOMS AND CUTSCENES RUN AT 30 FPS."},
 #endif
 #ifdef SKIPPABLE_CUTSCENES
    {QOL_ID_SKIPPABLE_CUTSCENES,                    "SKIPPABLE",              "CUTSCENES: ",      0x5E, // Some enum names in 'zoombox.h' are wrong. 0x5E are Klungo's sprites.
     "ALLOWS YOU TO SKIP MANY CUTSCENES IN THE GAME."},
 #endif
 #ifdef REIMPLEMENT_EXIT_TO_WITCHS_LAIR
    {QOL_ID_REIMPLEMENT_EXIT_TO_WITCHS_LAIR,        "EXIT TO WITCH'S LAIR: ", "",                 ZOOMBOX_SPRITE_5_GRUNTILDA_2,
     "REIMPLEMENTS EXIT TO WITCH'S LAIR OPTION IN THE PAUSE MENU. YOU CAN ONLY USE IT IF YOU'RE IN A LEVEL."},
 #endif
 #ifdef DONT_HOLD_Z_TO_USE_MOVES
    {QOL_ID_DONT_HOLD_Z_TO_USE_MOVES,               "DON'T HOLD Z",           "TO USE MOVES: ",   ZOOMBOX_SPRITE_D_KAZOOIE_1,
     "WHEN YOU USE TALON TROT OR WONDERWING, YOU DON'T NEED TO HOLD Z TO KEEP USING THE MOVE. TO EXIT, YOU CAN PRESS Z OR B."},
 #endif
 #ifdef ONLY_B_BUTTON_SKIPS_DIALOG
    {QOL_ID_ONLY_B_BUTTON_SKIPS_DIALOG,             "ONLY B BUTTON",          "SKIPS DIALOG: ",   ZOOMBOX_SPRITE_4_BANJO_1,
     "INSTEAD OF HOLDING L, R, AND B TO SKIP DIALOG, YOU CAN JUST PRESS B."},
 #endif
 #ifdef UNLOCK_PLACE_ALL_PUZZLE_PIECES
    {QOL_ID_UNLOCK_PLACE_ALL_PUZZLE_PIECES,         "UNLOCK PLACE ALL",       "PUZZLE PIECES: ",  ZOOMBOX_SPRITE_6_JIGGY_1,
     "UNLOCK THE ABILITY TO PLACE ALL JIGGIES IN A PICTURE BEFORE BOTTLES TEACHES YOU."},
 #endif
 #ifdef SAND_CASTLE_PERMANENTLY_DRAINED
    {QOL_ID_SAND_CASTLE_PERMANENTLY_DRAINED,        "SANDCASTLE DRAINED",     "PERMANENTLY: ",    ZOOMBOX_SPRITE_38_LEAKY,
     "THE SANDCASTLE IN TREASURE TROVE COVE BECOMES PERMANENTLY DRAINED WHEN YOU COLLECT THE SANDCASTLE JIGGY."},
 #endif
 #ifdef CLUCKER_CUTSCENE_VOLATILE_FLAG
    {QOL_ID_CLUCKER_CUTSCENE_VOLATILE_FLAG,         "CLUCKER CUTSCENE",       "PLAYS ONCE: ",     ZOOMBOX_SPRITE_55_ADULT_EEYRIE,
     "THE CUTSCENE THAT PLAYS WHEN YOU DEFEAT A CLUCKER WILL ONLY PLAY ONCE PER PLAY SESSION, INSTEAD OF WHEN YOU EXIT A LEVEL."},
 #endif
 #if defined(SHORTER_CHEATS) || defined(EASIER_CHEATS) || defined(ENTER_MORE_THAN_3_BANNED_CHEATS)
    {QOL_ID_CHEAT_CODES_OVERHAUL,                   "SANDCASTLE CHEAT",       "CODES OVERHAUL: ", ZOOMBOX_SPRITE_59_BLACK_SNIPPET,
     "MADE IMPROVEMENTS TO HOW YOU INPUT CHEAT CODES IN THE SANDCASTLE IN TREASURE TROVE COVE."},
 #endif
 #ifdef ADDITIONAL_CHEATS
    {QOL_ID_ADDITIONAL_CHEATS,                      "ADDITIONAL CHEAT",       "CODES: ",          ZOOMBOX_SPRITE_5B_CHEATO,
     "ADDS MORE CHEATS TO USE IN THE SANDCASTLE IN TREASURE TROVE COVE."},
 #endif

    {QOL_ID_NONE,                                   "END OF LIST",            "",                 ZOOMBOX_SPRITE_4_BANJO_1,
     "YOU SHOULDN'T BE ABLE TO READ THIS!"}
};
#endif

u8 *CONTROL_STICK_INSTRUCTIONS = "USE THE CONTROL STICK TO SELECT A GAME.";   
u8 *ERASE_INSTRUCTIONS = "PRESS A TO PLAY THE GAME OR Z TO ERASE IT!";
u8 *ERASE_CONFIRMATION = "ARE YOU SURE? PRESS A TO CONFIRM, OR B TO CANCEL";
#ifdef OPTIONS_MENU
u8 *OPTIONS_INSTRUCTIONS_L_BUTTON_ONE = "PRESS L TO VIEW THE OPTIONS MENU.";

u8 *OPTIONS_INSTRUCTIONS_CONTROL_STICK = "USE THE CONTROL STICK TO SCROLL UP AND DOWN.";
u8 *OPTIONS_INSTRUCTIONS_A_BUTTON = "PRESS A TO TURN THE OPTION ON OR OFF.";
u8 *OPTIONS_INSTRUCTIONS_L_BUTTON_TWO = "PRESS L TO READ WHAT THE OPTION DOES.";
u8 *OPTIONS_INSTRUCTIONS_B_BUTTON = "PRESS B TO GO BACK TO THE MAIN MENU.";
#endif

s32 gameNumber = -1;

f32 INITIAL_CAMERA_TARGETS[3][3] = {
    { -435.0f,      278.0f,  -159.0f },
    { 444.635437f, 216.0f,  -356.591675f },
    { 55.0f,      191.822906f, -905.96875f }
};

ActorAnimationInfo banjoSleepingAnimations[] = {
    { 0x000, 0.0f },
    { 0x24D, 9e+09f },
    { 0x24D, 2.0f },  
    { 0x24E, 1.0f },
    { 0x24F, 0.6f },  
    { 0x24D, 2.0f }
#ifdef OPTIONS_MENU
    ,
    { 0x000, 0.0f }, // GAME_SELECT_DONE
    { 0x24D, 2.0f }  // GAME_SELECT_OPTIONS_MENU
#endif
};
ActorInfo gameSelect_banjoSleeping = {
    MARKER_E4_CS_BK_SLEEPING, 0x195, ASSET_532_MODEL_BANJO_KAZOOIE_CUTSCENES,
    0x1, banjoSleepingAnimations,
    gameSelect_initAndUpdate, actor_update_func_80326224, gameSelect_zoomboxDraw,
    0, 0, 0.0f, 0
};

ActorAnimationInfo banjoGameboyAnimations[] = {
    { 0x000, 0.0f }, 
    { 0x250, 9e+09f },
    { 0x250, 4.5f }, 
    { 0x251, 1.0f },
    { 0x252, 0.67f }, 
    { 0x250, 4.5f }
#ifdef OPTIONS_MENU
    ,
    { 0x000, 0.0f }, // GAME_SELECT_DONE
    { 0x250, 4.5f }  // GAME_SELECT_OPTIONS_MENU
#endif
};
ActorInfo gameSelect_banjoGameboy = {
    MARKER_E5_CS_BK_GAMEBOY, 0x196, ASSET_532_MODEL_BANJO_KAZOOIE_CUTSCENES,
    0x1, banjoGameboyAnimations,
    gameSelect_update, actor_update_func_80326224, gameSelect_draw,
    0, 0, 0.0f, 0
};

ActorAnimationInfo banjoCookingAnimations[] = {
    { 0x000, 0.0f },
    { 0x24A, 9e+09f },  
    { 0x24A, 1.0f },
    { 0x24B, 1.0f },  
    { 0x24C, 1.0f },
    { 0x24A, 1.0f }
#ifdef OPTIONS_MENU
    ,
    { 0x000, 0.0f }, // GAME_SELECT_DONE
    { 0x24A, 1.0f }  // GAME_SELECT_OPTIONS_MENU
#endif
};
ActorInfo gameSelect_banjoCooking = {
    MARKER_E6_CS_BK_COOKING, 0x197, ASSET_532_MODEL_BANJO_KAZOOIE_CUTSCENES,
    0x1, banjoCookingAnimations,
    gameSelect_update, actor_update_func_80326224, gameSelect_draw,
    0, 0, 0.0f, 0
};

/* .bss */
// Fun level specific things- why would the devs define these here?
s32 mmhut_smashCount;
u32 chtreasureHunt_puzzleCurrentStep;

struct FF_StorageStruct* ffStorage;
s32 D_8037DCBC;
u8 gCompletedBottleBonusGames[7]; // bottle bonus puzzle?
u8 D_8037DCC7;
u8 D_8037DCC8;
u8 D_8037DCC9;
u8 D_8037DCCA;
u8 D_8037DCCB;
u8 D_8037DCCC;
u8 D_8037DCCD;
u8 D_8037DCCE[3];
s32 pad_8037DCD4;
s32 pad_8037DCD8;
#ifdef OPTIONS_MENU
u8 mainMenuStrCnt = 3;
u8 optionsMenuStrCnt = 4;
#endif

struct {
    u8 *controlInstruction;
    u8 *eraseInstruction;
#ifdef OPTIONS_MENU
    u8 *optionsInstruction;
#endif
} selectInstructions;

#ifdef OPTIONS_MENU
extern scrollingMenuStruct scrollingMenu;
#endif

s32 previousGameNumber;
bool isFileMoving; // Is the camera / player moving between save files?
GcZoombox *chGameSelectTopZoombox;
GcZoombox *chGameSelectBottomZoombox;
f32 cameraPositions[2][3];
f32 cameraDelta[2][3];
s32 cookingSoundEffectIndex;
bool isTopTextNotFinishedDisplaying;
f32 gameSelectCameraDelta;
f32 cycleInstructionsTimer;

/* .code */
Actor *gameSelect_draw(ActorMarker *marker, Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    // Get the game number from the actor. The actor ids start at 0xE4 so this will turn into 0 - 2.
    s32 game_number = marker->id - 0xE4;

    func_8033A45C(3, game_number);
    func_8033A45C(1, 1);
    func_8033A45C(4, 1);
    func_8033A45C(9, 1);
    func_8033A45C(5, 0);
    func_8033A45C(8, 0);
    func_8033A45C(6, 0);
    func_8033A45C(7, 0);
    func_8033A45C(0xC, 1);
    func_8033A45C(0xF, 1);

    // If this is the actor for the selected game, make Banjo normal- otherwise grey him out
    if (game_number == gameNumber) {
        modelRender_setEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        modelRender_setEnvColor(0x64, 0x64, 0x64, 0xFF);
    }

    return actor_draw(marker, gfx, mtx, vtx);
}

Actor *gameSelect_zoomboxDraw(ActorMarker *marker, Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    Actor *ret_val = gameSelect_draw(marker, gfx, mtx, vtx);

    if (chGameSelectBottomZoombox) {
        gczoombox_draw(chGameSelectBottomZoombox, gfx, mtx, vtx);
    }

    if (chGameSelectTopZoombox) {
        gczoombox_draw(chGameSelectTopZoombox, gfx, mtx, vtx);
    }
    
#ifdef OPTIONS_MENU
    scrollingMenu_zoomboxDraw(gfx, mtx, vtx);
#endif

    return ret_val;    
}

void topZoomboxCallback(s32 portraitId, s32 state) {
    // Is the zoombox state in finished?
    if (state == 3) {
        isTopTextNotFinishedDisplaying = FALSE;
    }
}

// Fancy trigonometry- please update the descriptions if you understand them  
void *calculateGameSelectCameraPosition(f32 from[3], f32 to[3], f32 deltaTime) {
    f32 sqrt_totals;
    f32 delta[3];
    s32 i;

    static s32 dummy_index; // Always zero
    static f32 bounciness; // This helps give the camera that "rubber band" quality when moving between saves
    static f32 sin_bounciness_half_pi;

    // At max, this can take ~3/4s of a second- this acts as that upper bound
    deltaTime = (deltaTime > 0.75) ? 0.75 : deltaTime;

    delta[0] = to[0] - from[0];
    delta[1] = to[1] - from[1];
    delta[2] = to[2] - from[2];
    dummy_index = dummy_index^1;

    sqrt_totals = sqrtf((delta[0] * delta[0]) + (delta[1] * delta[1]) + (delta[2] * delta[2]));

    if (sqrt_totals < 10.0f) {
        sqrt_totals = 500.0f;
    }

    bounciness = 1.0 + (9.0f / sqrtf(sqrt_totals));
    sin_bounciness_half_pi = sinf(bounciness * 1.5707963267948966);

    for (i = 0; i < 3; i++) {
        cameraDelta[dummy_index][i] = from[i] + 
            (
                ((to[i] - from[i]) * sinf((((deltaTime / 0.75) * 3.1415926535897931) / 2) * bounciness)) 
                / sin_bounciness_half_pi
            );
        cameraPositions[dummy_index][i] += (cameraDelta[dummy_index][i] - cameraPositions[dummy_index][i]) / 5.0;
    }

    return &cameraPositions[dummy_index];
}

void setGameInformationZoombox(s32 gamenum) {
    u8 *zoombox_strings[2];
    static u8 upperTextLine[0x20];
    static u8 lowerTextLine[0x20];

    debugScoreStates();
    gameNumber = gamenum;
    clearScoreStates();

    if (gameFile_isNotEmpty(gamenum)) {
        gameFile_load(gamenum);
        D_8037DCCE[gamenum] = (itemscore_timeScores_get(LEVEL_6_LAIR)) ? 1 : 0;
    
        strcpy(upperTextLine, "");
        strcat(upperTextLine, "GAME ");

        // Game number to human readable. Interestingly, gamenumber 1 is Banjo playing gameboy as opposed to cooking
        switch (gamenum) {
            case 0: //L802C4820
                strIToA(upperTextLine, 1);
                break;
            case 1: //L802C4838
                strIToA(upperTextLine, 3);
                break;
            case 2: //L802C484C
                strIToA(upperTextLine, 2);
                break;
        } //L802C4858

        strcat(upperTextLine, ": TIME ");
        strcat(upperTextLine, gcpausemenu_TimeToA(itemscore_timeScores_getTotal()));
        strcat(upperTextLine, ",");
        strcat(upperTextLine, "");

        strcpy(lowerTextLine, "");
        strIToA(lowerTextLine, jiggyscore_total());
        strcat(lowerTextLine, " JIGSAW");
        if (jiggyscore_total() != 1) {
            strcat(lowerTextLine, "S");
        }

        strcat(lowerTextLine, ", ");
        strIToA(lowerTextLine, itemscore_noteScores_getTotal());
        strcat(lowerTextLine, " NOTE");
        if (itemscore_noteScores_getTotal() != 1) {
            strcat(lowerTextLine, "S");
        }

        strcat(lowerTextLine, ".");
        strcat(lowerTextLine, "");
    } else { //L802C49AC
        D_8037DCCE[gamenum] = 0;
        strcpy(upperTextLine, "");
        strcat(upperTextLine, "GAME ");

        // Game number to human readable
        switch (gamenum){
            case 0:
                strIToA(upperTextLine, 1);
                break;
            case 1:
                strIToA(upperTextLine, 3);
                break;
            case 2:
                strIToA(upperTextLine, 2);
                break;
        } //L802C4A40

        strcat(upperTextLine, ": EMPTY");
        strcpy(lowerTextLine, "");
    } //L802C4A68

    // Can't delete backslash
    zoombox_strings[0] = upperTextLine;\
    zoombox_strings[1] = lowerTextLine;

    func_8031877C(chGameSelectBottomZoombox);
    gczoombox_setStrings(chGameSelectBottomZoombox, 2, zoombox_strings);
    gczoombox_maximize(chGameSelectBottomZoombox);
    gczoombox_resolve_minimize(chGameSelectBottomZoombox);
}

void eraseGame(s32 gamenum) {
    gameFile_clear(gamenum);
    setGameInformationZoombox(gamenum);
}

void gameSelect_free(Actor *this){
    int i;

    if (chGameSelectTopZoombox) {
        gczoombox_free(chGameSelectTopZoombox);
        chGameSelectTopZoombox = NULL;
    }

    if (chGameSelectBottomZoombox) {
        gczoombox_free(chGameSelectBottomZoombox);
        chGameSelectBottomZoombox = NULL;
    }

#ifdef OPTIONS_MENU
    scrollingMenu_zoomboxFree();
#endif

    for (i = 0; i < 3; i++) {
        gameFile_8033CFD4(i);
    }

    if (cookingSoundEffectIndex) {
        func_802F9D38(cookingSoundEffectIndex);
        cookingSoundEffectIndex = NULL;
    }

    comusic_8025AB44(COMUSIC_73_GAMEBOY, 0, 4000);
    func_8025AABC(COMUSIC_73_GAMEBOY);
    func_8025AB00();
}

// Using the Banjo actor, spawn in the needed actors for their "scene"
void spawnGameSelectProps(ActorMarker *marker) {
    Actor *this;
    s32 game_number;
    Actor *prop;
    f32 scale;
    game_number = marker->id - 0xE4; // Actor ID to game number
    this = marker_getActor(marker);
    scale = this->scale;
    prop = actor_spawnWithYaw_f32(game_number + ACTOR_198_BANJOS_BED, // Bed -> Chair -> Stove 
        this->position, (s32)this->yaw);
    prop->scale = scale;
}

#ifdef OPTIONS_MENU
void optionsMenu_init(void) {
    int i = code94620_func_8031B5B0();

    scrollingMenu.selection = scrollingMenu.onScreenSelection = scrollingMenu.selectDelay = scrollingMenu.menuMoveDirection = 0;
    scrollingMenu.moveDelay = -1;
    scrollingMenu.onLowerHalfOfMenu = scrollingMenu.movingMenu = scrollingMenu.menuFinishedDisplaying = scrollingMenu.textResetOnce = scrollingMenu.bottomPortraitOpacityFix = FALSE;
    scrollingMenu.menuCycleInstructionsTimer = 0.0f;
    if (scrollingMenu.topZoombox) {
        gczoombox_free(scrollingMenu.topZoombox);
        scrollingMenu.topZoombox = NULL;
    }
    if (optionsZoomboxData[1].id != QOL_ID_NONE) {
        scrollingMenu.instructions.one = (&OPTIONS_INSTRUCTIONS_CONTROL_STICK)[i];
        scrollingMenu.instructions.two = (&OPTIONS_INSTRUCTIONS_A_BUTTON)[i];
        scrollingMenu.instructions.three = (&OPTIONS_INSTRUCTIONS_L_BUTTON_TWO)[i];
        scrollingMenu.instructions.four = (&OPTIONS_INSTRUCTIONS_B_BUTTON)[i];
    } else {
        scrollingMenu.instructions.one = (&OPTIONS_INSTRUCTIONS_A_BUTTON)[i];
        scrollingMenu.instructions.two = (&OPTIONS_INSTRUCTIONS_L_BUTTON_TWO)[i];
        scrollingMenu.instructions.three = (&OPTIONS_INSTRUCTIONS_B_BUTTON)[i];
        scrollingMenu.instructions.four = NULL;
        optionsMenuStrCnt = 3;
    }
    for (i = 0; i < 6; i++) {
        if (scrollingMenu.zoombox[i]) {
            gczoombox_free(scrollingMenu.zoombox[i]);
            scrollingMenu.zoombox[i] = NULL;
        }
    }
}

void optionsMenu_zoombox_callback(s32 portrait_id, s32 zoombox_state) {
    u8 i;
    
    if (zoombox_state == 2) {
        for (i = 1; i < 6; i++) {
            if (scrollingMenu.zoombox[i]) {
                gczoombox_highlight(scrollingMenu.zoombox[i], FALSE);
            }
        }
    }
}

void update_optionsMenu_zoombox_strings(u8 selectionIndex, u8 zoomboxIndex, bool instantlyPrintStrings) {
    u8 *zoombox_strings[2];
    static u8 upperTextLine[6][0x20];
    static u8 lowerTextLine[6][0x20];
    u8 *status;
    bool printStatusOnLowerLine = (strcmp("", optionsZoomboxData[selectionIndex].secondStr) || (strlen(optionsZoomboxData[selectionIndex].firstStr) >= 19));

    strcpy(upperTextLine[zoomboxIndex], "");
    strcat(upperTextLine[zoomboxIndex], optionsZoomboxData[selectionIndex].firstStr);
    strcpy(lowerTextLine[zoomboxIndex], "");
    strcat(lowerTextLine[zoomboxIndex], optionsZoomboxData[selectionIndex].secondStr);
    if (!get_optionsMenu_flags(selectionIndex)) {
        status = "ON";
        scrollingMenu.zoombox[zoomboxIndex]->textRGB[1] = 0xFF;
        scrollingMenu.zoombox[zoomboxIndex]->textRGB[0] = scrollingMenu.zoombox[zoomboxIndex]->textRGB[2] = 0x00;
    } else {
        status = "OFF";
        scrollingMenu.zoombox[zoomboxIndex]->textRGB[0] = 0xFF;
        scrollingMenu.zoombox[zoomboxIndex]->textRGB[1] = scrollingMenu.zoombox[zoomboxIndex]->textRGB[2] = 0x00;
    }

    if (printStatusOnLowerLine) {
        strcat(lowerTextLine[zoomboxIndex], status);
        scrollingMenu.zoombox[zoomboxIndex]->textYOffset = -1;
    } else {
        strcat(upperTextLine[zoomboxIndex], status);
        scrollingMenu.zoombox[zoomboxIndex]->textYOffset = 4;
    }

    zoombox_strings[0] = upperTextLine[zoomboxIndex];
    zoombox_strings[1] = lowerTextLine[zoomboxIndex];

    gczoombox_setStrings(scrollingMenu.zoombox[zoomboxIndex], 2, zoombox_strings);

    if (instantlyPrintStrings) {
        do {
            gczoombox_update(scrollingMenu.zoombox[zoomboxIndex]);
        } while (scrollingMenu.zoombox[zoomboxIndex]->state != 0xA);
    }
}

void open_mainMenu_zoomboxes(Actor *this) {
    s32 gamenum = this->marker->id - 0xE4;

    scrollingMenu_zoomboxFree();

    gczoombox_free(chGameSelectBottomZoombox);
    chGameSelectBottomZoombox = NULL;

    chGameSelectBottomZoombox = gczoombox_new(0xA0, ZOOMBOX_SPRITE_C_BANJO_2, 2, 0, NULL);
    gczoombox_open(chGameSelectBottomZoombox);
    gczoombox_func_803184C8(chGameSelectBottomZoombox, 30.0f, 5, 2, 0.4f, 0, 0);
    setGameInformationZoombox(gamenum);
    
    chGameSelectTopZoombox = gczoombox_new(0xA, ZOOMBOX_SPRITE_D_KAZOOIE_1, 2, 1, topZoomboxCallback);
    gczoombox_setStrings(chGameSelectTopZoombox, mainMenuStrCnt, (char **)&selectInstructions);
    gczoombox_open(chGameSelectTopZoombox);
    gczoombox_maximize(chGameSelectTopZoombox);

    timedFunc_set_2(30.0f * time_getDelta(), (GenFunction_2) subaddie_set_state, (s32)this, GAME_SELECT_IDLE);
}

void open_optionsMenu_zoomboxes(void) {
    u8 i;

    optionsMenu_init();

    gczoombox_free(chGameSelectTopZoombox);
    chGameSelectTopZoombox = NULL;
    
    gczoombox_free(chGameSelectBottomZoombox);
    chGameSelectBottomZoombox = NULL;
    
    scrollingMenu.topZoombox = gczoombox_new(0xA, ZOOMBOX_SPRITE_10_MUMBO_1, 2, 0, NULL);
    gczoombox_setStrings(scrollingMenu.topZoombox, optionsMenuStrCnt, (char **)&scrollingMenu.instructions);
    gczoombox_open(scrollingMenu.topZoombox);
    gczoombox_maximize(scrollingMenu.topZoombox);

    chGameSelectBottomZoombox = gczoombox_new(0x0, ZOOMBOX_SPRITE_C_BANJO_2, 2, 0, NULL); // 'chGameSelectBottomZoombox' needs to not be NULL in order for Game Select to update.

    for (i = 0; i < 6; i++) {
        f32 delay = ((f32)(MIN(i, 4)) / 10.0f) + 0.1f;
        bool atLastIndex = (optionsZoomboxData[i + 1].id == QOL_ID_NONE);
        
        scrollingMenu.zoombox[i] = gczoombox_new((30 * i + 54), optionsZoomboxData[i].portrait, 2, 0, optionsMenu_zoombox_callback);
        gczoombox_func_803184C8(scrollingMenu.zoombox[i], 60.0f, 5, 2, 0.3f, 0, 0);
        func_80318640(scrollingMenu.zoombox[i], 0x40, 0.75f, 0.99999f, 0);
        if (i != 5) {
            func_80318760(scrollingMenu.zoombox[i], 8000);
        } else {
            func_80318760(scrollingMenu.zoombox[i], 0);
            scrollingMenu.zoombox[i]->zoomboxAlpha = scrollingMenu.zoombox[i]->textAlpha = 0x00;
            scrollingMenu.bottomPortraitOpacityFix = TRUE;
        }
        
        update_optionsMenu_zoombox_strings(i, i, FALSE);
        
        timedFunc_set_1(delay, (GenFunction_1) gczoombox_open, (s32)scrollingMenu.zoombox[i]);
        timedFunc_set_1(delay, (GenFunction_1) gczoombox_maximize, (s32)scrollingMenu.zoombox[i]);

        if (atLastIndex) {
            break;
        }
    }

    timedFunc_set_1(31.0f * time_getDelta(), (GenFunction_1) set_menu_finished_displaying_state, TRUE);
}

void close_mainMenu_zoomboxes(void) {
    func_803188B4(chGameSelectTopZoombox);
    gczoombox_close(chGameSelectTopZoombox);

    func_803188B4(chGameSelectBottomZoombox);
    gczoombox_close(chGameSelectBottomZoombox);

    scrollingMenu.menuFinishedDisplaying = FALSE;
}

void update_optionsMenu_zoombox_data(void) {
    if (scrollingMenu.movingMenu) {
        u8 i;
        u8 topZoomboxSelection = scrollingMenu.selection - scrollingMenu.onScreenSelection - (u8)scrollingMenu.onLowerHalfOfMenu;
        for (i = 0; i < 6; i++) {
            if (scrollingMenu.zoombox[i]) {
                func_8031877C(scrollingMenu.zoombox[i]);
                update_optionsMenu_zoombox_strings((i + topZoomboxSelection), i, TRUE);
                zoombox_setSprite(scrollingMenu.zoombox[i], optionsZoomboxData[i + topZoomboxSelection].portrait);
            }
        }
    }
}
#endif

void gameSelect_update(Actor *this) {
    int game_number;
    int game_numbers_match;
    s32 side_buttons[3];

    s32 *unused_padding;
    s32 unused_padding_2;
    s32 unused_padding_3;

    s32 face_buttons[3];

    s32 unused_padding_4;

    f32 joystick;
    f32 delta_time; 
    int i;
    struct5Bs *sp48;
    f32 function_time;
    s32 previous_game_number;
    f32 sp34[3];
#ifdef OPTIONS_MENU
    f32 *joystick_y;
#endif

    // Actor ID to game number
    game_number = this->marker->id - 0xE4;

    game_numbers_match = (game_number == gameNumber);
    delta_time = time_getDelta();

    if (chGameSelectBottomZoombox == NULL) {
        return;
    }

    if (!this->initialized) {
        __spawnQueue_add_1((GenFunction_1)spawnGameSelectProps, reinterpret_cast(s32, this->marker));
        func_802C7318(this);
        this->unk130 = func_802C71F0;

        if (game_number == 0) {
            func_802C75A0(this, 1);
            func_802C74F4(this, 0, 1.0f);
            func_802C74F4(this, 1, 1.0f);
        }

        this->initialized = TRUE;
    }

    func_802C7478(this);

    if (!game_numbers_match) {
        if (this->state != GAME_SELECT_INITIALIZE) {
            subaddie_set_state(this, GAME_SELECT_INITIALIZE);
        }

        return;
    }

    controller_copySideButtons(0, side_buttons);
    controller_copyFaceButtons(0, face_buttons);
    controller_getJoystick(0, &joystick);
#ifdef OPTIONS_MENU
    joystick_y = &joystick;
    joystick_y++;
#endif

    switch (this->state) {
        case GAME_SELECT_IDLE:
        case GAME_SELECT_ERASE_CONFIRMATION:
#ifdef OPTIONS_MENU
        case GAME_SELECT_OPTIONS_MENU:
#endif
            switch (game_number) {
                case 0: // Sleeping Banjo; cycle his snoring sfx
                    if (actor_animationIsAt(this, 0.1f)) {
                        gcsfx_playAtSampleRate(SFX_5D_BANJO_RAAOWW, 8000);
                    }

                    if (actor_animationIsAt(this, 0.7f)) {
                        gcsfx_playAtSampleRate(SFX_5E_BANJO_PHEWWW, 8000);
                    }

                    break;

                case 1: // Gaming Banjo; randomly play some game low bloop sounds
                    if (randf() < 0.1) {
                        gcsfx_playWithPitch(MIN(2.0f, randf() * 3.0f) + SFX_137_GAMEBOY_BOIN, 1.0f, 12000);
                    }

                    break;

                case 2: // Cooking Banjo; randomly play bubble popping at random pitch
                    if (randf() < 0.03) {
                        gcsfx_playWithPitch(SFX_3ED_BUBBLE_POP, randf() * 0.3 + 0.7, 15000);
                    }

                    break;
            }
            break;
    }

    if (!func_8038AAB0()) {
        switch (this->state) {
            case GAME_SELECT_INITIALIZE:
                if (game_number == 1) {
                    gcsfx_playAtSampleRate(SFX_136_GAMEBOY_STARTUP, 15000);
                    timedFunc_set_3(0.25f, (GenFunction_3)comusic_8025AB44, COMUSIC_73_GAMEBOY, -1, 2000);
                    func_8025A58C(0, 2000);
                } else {
                    comusic_8025AB44(COMUSIC_73_GAMEBOY, 0, 4000);
                    func_8025A58C(-1, 2000);
                }

                if (game_number == 2) {
                    cookingSoundEffectIndex = func_802F9AA8(SFX_12B_BOILING_AND_BUBBLING);
                    func_802F9F80(cookingSoundEffectIndex, 0.5f, 9000000000.0f, 0.5f);
                    func_802F9DB8(cookingSoundEffectIndex, 0.9f, 0.9f, 0.0f);
                    func_802FA060(cookingSoundEffectIndex, 15000, 15000, 0.0f);
                } else if (cookingSoundEffectIndex) {
                    func_802F9D38(cookingSoundEffectIndex);
                    cookingSoundEffectIndex = NULL;
                }

                setGameInformationZoombox(game_number);
                subaddie_set_state(this, GAME_SELECT_IDLE);
                break;

            case GAME_SELECT_ERASE_CONFIRMATION:
                // Don't let the player make a decision until the text has gone through                
                if (isTopTextNotFinishedDisplaying == FALSE 
                    && (face_buttons[FACE_BUTTON(BUTTON_A)] == 1 || face_buttons[FACE_BUTTON(BUTTON_B)] == 1)) {

                    if (face_buttons[FACE_BUTTON(BUTTON_A)] == 1) {
                        eraseGame(game_number);
                        coMusicPlayer_playMusic(COMUSIC_2B_DING_B, 22000);
                    }

                    subaddie_set_state(this, GAME_SELECT_IDLE);
                    func_8031877C(chGameSelectTopZoombox);
#ifdef OPTIONS_MENU
                    gczoombox_setStrings(chGameSelectTopZoombox, mainMenuStrCnt, (char **)&selectInstructions);
#else
                    gczoombox_setStrings(chGameSelectTopZoombox, 2, (char **)&selectInstructions);
#endif
                    cycleInstructionsTimer = 0.0f;
                }

                break;

            case GAME_SELECT_STARTING:
            case GAME_SELECT_STARTING_SILLY:
                if (anctrl_isStopped(this->anctrl)) {
                    chBottlesBonus_resetCompleted();

                    if (!gameFile_isNotEmpty(game_number)) { // New game
                        timedFunc_set_3(0.0f, (GenFunction_3) transitionToMap, MAP_85_CS_SPIRAL_MOUNTAIN_3, 0, 1);
                    } else {
                        function_time = 0.0f;

                        // Add a little extra time for the silly animation
                        if (this->state == GAME_SELECT_STARTING_SILLY && (game_number == 0 || game_number == 1)) {
                            function_time = 0.25f;
                        }

                        // If player has gone into the lair, spawn them there
                        if (chmole_learnedAllSpiralMountainAbilities() && fileProgressFlag_get(FILEPROG_BD_ENTER_LAIR_CUTSCENE)) {
                            timedFunc_set_2(function_time, (GenFunction_2) warp_lairEnterLairFromSMLevel, 0, 0);
                        } else { // Otherwise, they're still in Spiral Mountain
                            timedFunc_set_2(function_time, (GenFunction_2) warp_smExitBanjosHouse, 0, 0);
                        }

                        timedFunc_set_1(function_time, (GenFunction_1) gsworld_setEnableUpdate, 1);
                    }

                    this->state = GAME_SELECT_DONE;
                }
                break;

            case GAME_SELECT_IDLE:
                if (side_buttons[SIDE_BUTTON(BUTTON_Z)] == 1) { // Delete file
                    if (gameFile_isNotEmpty(game_number)) {
                        func_8031877C(chGameSelectTopZoombox);
                        func_803183A4(chGameSelectTopZoombox, (&ERASE_CONFIRMATION)[code94620_func_8031B5B0()]);
                        isTopTextNotFinishedDisplaying = TRUE;
                        subaddie_set_state(this, GAME_SELECT_ERASE_CONFIRMATION);
                    } else {
                        coMusicPlayer_playMusic(COMUSIC_2C_BUZZER, 22000);
                    }
                } else if (face_buttons[FACE_BUTTON(BUTTON_A)] == 1) { // Select file
                    if (gameFile_isNotEmpty(game_number)) {
                        if (randf() < 0.1) { // Rarely activate "silly" animations
                            switch (game_number) {
                                case 0: // Sleeping Banjo; Out the window
                                    gcsfx_playAtSampleRate(SFX_31_BANJO_OHHWAAOOO, 28000);
                                    gcsfx_play(SFX_135_CARTOONY_SPRING);
                                    timedFunc_set_2(0.4f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_13A_GLASS_BREAKING_7, 0x7FFF);
                                    timedFunc_set_2(0.9f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_150_PORCELAIN_CRASH, 0x7FFF);
                                    timedFunc_set_2(1.0f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_151_CAT_MEOW, 0x7FFF);
                                    break;
                                case 1: // Gaming Banjo; Springy chair
                                    timedFunc_set_2(0.4f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_31_BANJO_OHHWAAOOO, 28000);
                                    timedFunc_set_2(0.2f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_E_SHOCKSPRING_BOING, 28000);
                                    gcsfx_play(SFX_2D_KABOING);
                                    break;
                                case 2: // Cooking Banjo; Spin the kitchen
                                    timedFunc_set_2(0.15f, (GenFunction_2)gcsfx_playAtSampleRate, SFX_32_BANJO_EGHEE, 28000);
                                    gcsfx_playAtSampleRate(SFX_3F6_RUBBING, 28000);
                                    gcsfx_play(SFX_8F_SNOWBALL_FLYING);
                                    break;
                            }

                            subaddie_set_state(this, GAME_SELECT_STARTING_SILLY);
                            levelSpecificFlags_set(game_number + LEVEL_FLAG_35_UNKNOWN, 1);
                        } else {
                            sfxsource_playHighPriority(SFX_3EA_BANJO_GUH_HUH);
                            subaddie_set_state(this, GAME_SELECT_STARTING);
                        }
                    } else { // Start new game
                        gcsfx_playAtSampleRate(SFX_4F_BANJO_WAHOO, 28000);
                        subaddie_set_state(this, GAME_SELECT_STARTING);
                    }

                    if (game_number == 0) {
                        func_802C75A0(this, 2);
                    }

                    if (game_number == 1) {
                        comusic_8025AB44(COMUSIC_73_GAMEBOY, 0, 4000);
                    }
                    
                    func_8025A58C(0, 0x1f4);
                    actor_playAnimationOnce(this);

                }
#ifdef OPTIONS_MENU
                  else if ((side_buttons[SIDE_BUTTON(BUTTON_L)] == 1) && (optionsZoomboxData[0].id != QOL_ID_NONE)) {
                    close_mainMenu_zoomboxes();
                    timedFunc_set_0(1.0f, (GenFunction_0) open_optionsMenu_zoomboxes);
                    subaddie_set_state(this, GAME_SELECT_OPTIONS_MENU);
                    cycleInstructionsTimer = 0.0f;
                }
#endif
                  else {
                    if ((0.7 < ((0.0f <= joystick) ? joystick : -joystick)) && isFileMoving == FALSE) {
                        previous_game_number = gameNumber;

                        // Joystick went left
                        if (joystick < 0.0f) {
                            isFileMoving = TRUE;

                            // Switch to file to the left
                            switch (gameNumber) {
                                case 0:
                                    isFileMoving = FALSE;
                                    break;

                                case 1:
                                    gameNumber = 2;
                                    break;

                                case 2:
                                    gameNumber = 0;
                                    break;
                            }
                        } else { // Joystick went right
                            isFileMoving = TRUE;

                            // Switch to file to the right
                            switch (gameNumber) {
                                case 0:
                                    gameNumber = 2;
                                    break;
                                case 1:
                                    isFileMoving = FALSE;
                                    break;
                                case 2:
                                    gameNumber = 1;
                                    break;
                            }
                        }

                        if (isFileMoving) {
                            previousGameNumber = previous_game_number;
                            gameSelectCameraDelta = 0.0f;
                        }
                    } else {
                        if (((0.0f <= joystick) ? joystick : -joystick) < 0.3) {
                            isFileMoving = FALSE;
                        }
                    }
                }

                if (isTopTextNotFinishedDisplaying == FALSE) {
                    cycleInstructionsTimer += delta_time;
                    if (20.0 < cycleInstructionsTimer) {
                        func_8031877C(chGameSelectTopZoombox);
#ifdef OPTIONS_MENU
                        gczoombox_setStrings(chGameSelectTopZoombox, mainMenuStrCnt, (char **)&selectInstructions);
#else
                        gczoombox_setStrings(chGameSelectTopZoombox, 2, (char **)&selectInstructions);
#endif
                        cycleInstructionsTimer = 0.0f;
                    }
                }

                break;

            case GAME_SELECT_DONE:
                break;
            
#ifdef OPTIONS_MENU
            case GAME_SELECT_OPTIONS_MENU:
                if (scrollingMenu.menuFinishedDisplaying) {
                    if (scrollingMenu.moveDelay > 0) {
                        scrollingMenu.moveDelay--;

                        if (scrollingMenu.moveDelay == 5) {
                            update_optionsMenu_zoombox_data();
                            update_scrollingMenu_zoombox_highlights();
                        }

                        if (scrollingMenu.movingMenu) {
                            for (i = 0; i < 6; i++) {
                                if (scrollingMenu.zoombox[i]) {
                                    update_scrollingMenu_zoombox_y_pos(i);

                                    if ((i == 0) || (i == 5)) {
                                        update_scrollingMenu_zoombox_transparency(i);
                                    }
                                }
                            }
                        }
                    } else if (0.75 < *joystick_y) {
                        reset_scrollingMenu_zoombox_y_pos_and_transparency();

                        if ((s32) scrollingMenu.selection > 0) {
                            scrollingMenu.selection--;
                            scrollingMenu.menuMoveDirection = -1;

                            update_scrollingMenu_info();
                            
                            scrollingMenu.moveDelay = 6;
                        }
                    } else if (*joystick_y < -0.75) {
                        reset_scrollingMenu_zoombox_y_pos_and_transparency();

                        if (optionsZoomboxData[(s32) scrollingMenu.selection + 1].id != QOL_ID_NONE) {
                            scrollingMenu.selection++;
                            scrollingMenu.menuMoveDirection = 1;

                            update_scrollingMenu_info();
                            
                            scrollingMenu.moveDelay = 6;
                        }
                    } else {
                        reset_scrollingMenu_zoombox_y_pos_and_transparency();
                    }

                    if (scrollingMenu.selectDelay > 0) {
                        scrollingMenu.selectDelay--;
                    } else if ((face_buttons[FACE_BUTTON(BUTTON_A)] == 1) && (scrollingMenu.moveDelay < 6)) {
                        bool inverseState = !get_optionsMenu_flags(scrollingMenu.selection);
                        u8 currZoombox = scrollingMenu.onScreenSelection + (u8)scrollingMenu.onLowerHalfOfMenu;

                        set_optionsMenu_flags(scrollingMenu.selection, inverseState);
                        scrollingMenu.selectDelay = 10;
                        
                        func_8031877C(scrollingMenu.zoombox[currZoombox]);
                        update_optionsMenu_zoombox_strings(scrollingMenu.selection, currZoombox, FALSE);

                        coMusicPlayer_playMusic(COMUSIC_2B_DING_B, 22000);
                    } else if (face_buttons[FACE_BUTTON(BUTTON_B)] == 1) {
                        scrollingMenu.bottomPortraitOpacityFix = FALSE;
                        close_scrollingMenu_zoomboxes();
                        timedFunc_set_1(1.0f, (GenFunction_1) open_mainMenu_zoomboxes, (s32)this);
                    } else if ((side_buttons[SIDE_BUTTON(BUTTON_L)] == 1) && ((1.0f < scrollingMenu.menuCycleInstructionsTimer) || scrollingMenu.textResetOnce)) {
                        func_8031877C(scrollingMenu.topZoombox);
                        gczoombox_setStrings(scrollingMenu.topZoombox, 1, (char **)&optionsZoomboxData[scrollingMenu.selection].information);
                        scrollingMenu.menuCycleInstructionsTimer = 0.0f;
                        scrollingMenu.textResetOnce = FALSE;
                    }

                    scrollingMenu.menuCycleInstructionsTimer += delta_time;
                    if (20.0f < scrollingMenu.menuCycleInstructionsTimer) {
                        func_8031877C(scrollingMenu.topZoombox);
                        gczoombox_setStrings(scrollingMenu.topZoombox, optionsMenuStrCnt, (char **)&scrollingMenu.instructions);
                        scrollingMenu.menuCycleInstructionsTimer = 0.0f;
                        scrollingMenu.textResetOnce = TRUE;
                    }
                /*
                 * Small issue where gczoombox_draw will try to increase the value of 'unk168' when the zoombox opens, which raises the opacity of the portrait.
                 * This is a quick and easy fix to keep very bottom zoombox portrait invisible when the options menu opens.
                 */
                } else if (scrollingMenu.bottomPortraitOpacityFix) {
                    scrollingMenu.zoombox[5]->unk168 = 0x00;
                }

                scrollingMenu_zoomboxUpdate();
                break;
#endif
        }
    }

    gameSelectCameraDelta += delta_time;
    sp48 = func_803097A0();

    if (this->marker->unk14_21) {
        for (i = 0; i < 3; i++) {
            func_8034A174(sp48, i + 5, sp34);
            ml_vec3f_copy(INITIAL_CAMERA_POSITIONS[i], sp34);
        }
    }

    ncStaticCamera_setPositionAndTarget(
        calculateGameSelectCameraPosition(INITIAL_CAMERA_POSITIONS[previousGameNumber], INITIAL_CAMERA_POSITIONS[gameNumber], gameSelectCameraDelta), 
        calculateGameSelectCameraPosition(INITIAL_CAMERA_TARGETS[previousGameNumber], INITIAL_CAMERA_TARGETS[gameNumber], gameSelectCameraDelta)
    );

    if (this->marker->unk14_21) {
        osViBlack(0);
    }
}

// Update function for when the scene first loads, set on the sleeping Banjo actor
void gameSelect_initAndUpdate(Actor * this){
    int i = code94620_func_8031B5B0();

    selectInstructions.controlInstruction = (&CONTROL_STICK_INSTRUCTIONS)[i];
    selectInstructions.eraseInstruction = (&ERASE_INSTRUCTIONS)[i];
#ifdef OPTIONS_MENU
    if (optionsZoomboxData[0].id != QOL_ID_NONE) {
        selectInstructions.optionsInstruction = (&OPTIONS_INSTRUCTIONS_L_BUTTON_ONE)[i];
    } else {
        selectInstructions.optionsInstruction = NULL;
        mainMenuStrCnt = 2;
    }
#endif

    if (!this->initialized) {
        gameFile_8033CE40();

        if (chGameSelectBottomZoombox == NULL) {
            chGameSelectBottomZoombox = gczoombox_new(0xA0, ZOOMBOX_SPRITE_C_BANJO_2, 2, 0, NULL);
            gczoombox_open(chGameSelectBottomZoombox);
            gczoombox_func_803184C8(chGameSelectBottomZoombox, 30.0f, 5, 2, 0.4f, 0, 0);
        }

        if (chGameSelectTopZoombox == NULL) {
            chGameSelectTopZoombox = gczoombox_new(0xA, ZOOMBOX_SPRITE_D_KAZOOIE_1, 2, 1, topZoomboxCallback);
#ifdef OPTIONS_MENU
            gczoombox_setStrings(chGameSelectTopZoombox, mainMenuStrCnt, (char **)&selectInstructions);
#else
            gczoombox_setStrings(chGameSelectTopZoombox, 2, (char **)&selectInstructions);
#endif
            gczoombox_open(chGameSelectTopZoombox);
            gczoombox_maximize(chGameSelectTopZoombox);
        }

        marker_setFreeMethod(this->marker, gameSelect_free);
        isFileMoving = FALSE;
        debugScoreStates();
        clearScoreStates();
        previousGameNumber = 0;
        gameNumber = 0;
        cameraPositions[1][0] = INITIAL_CAMERA_POSITIONS[0][0];
        cameraPositions[1][1] = INITIAL_CAMERA_POSITIONS[0][1];
        cameraPositions[1][2] = INITIAL_CAMERA_POSITIONS[0][2];

        cameraPositions[0][0] = INITIAL_CAMERA_TARGETS[0][0];
        cameraPositions[0][1] = INITIAL_CAMERA_TARGETS[0][1];
        cameraPositions[0][2] = INITIAL_CAMERA_TARGETS[0][2];
        gameSelectCameraDelta = 0.75f;
        cycleInstructionsTimer = func_8038AAB0(&INITIAL_CAMERA_TARGETS[0], &previousGameNumber) ? 20.0 : 0.0;
        actor_collisionOff(this);
        coMusicPlayer_playMusic(COMUSIC_73_GAMEBOY, 0);
    }

    if (!func_8038AAB0()) {
        if (chGameSelectBottomZoombox) {
            gczoombox_update(chGameSelectBottomZoombox);
        }

        if (chGameSelectTopZoombox) {
            gczoombox_update(chGameSelectTopZoombox);
        }
    }

    gameSelect_update(this);
}

void gameSelect_saveAndExit(void) {
    s32 level_id = level_get();
    s32 is_map_game_over = gsworld_getMap() == MAP_83_CS_GAME_OVER_MACHINE_ROOM;

    // Within bounds of levels. 0xD is 1 more than the amount of levels in the game.
    s32 is_level_id_valid = (0 < level_id && level_id < 0xD);

    if ((is_level_id_valid || is_map_game_over)
        && (gameNumber != -1 && !func_802E4A08() && gsworld_getMap() != MAP_91_FILE_SELECT)) {

        gameFile_save(gameNumber);
        gameFile_8033CFD4(gameNumber);
    }
}

s32 gameSelect_getGameNumber(void) {
    return gameNumber;
}

void gameSelect_setGameNumber(s32 num) {
    gameNumber = num;
}

void gameSelect_resetGameNumber(void) {
    gameNumber = -1;
}

#ifdef OPTIONS_MENU
bool is_qol_feature_enabled(enum qol_id id) {
    u8 i;

    for (i = 0; ((i < id) && (optionsZoomboxData[i].id != QOL_ID_NONE)); i++) {
        if (optionsZoomboxData[i].id == id) {
            return !get_optionsMenu_flags(i);
        }
    }
    return FALSE;
}
#endif
