#include <ultra64.h>
#include "core1/core1.h"
#include "functions.h"
#include "variables.h"

#include "config.h"


void func_802CD898(Actor *);
void func_802CD8C0(Actor *);
void func_802CDAC4(Actor *);
void func_802CDB18(Actor *);

/* .data */
ActorInfo D_80367160 = {0x12, 0x66, 0, 0, NULL, 
    func_802CD898, func_802CD8C0, func_80325340,
    0, 0, 0.0f, 0
}; 

ActorInfo D_80367184 = {0x12, 0x6C, 0, 0, NULL, 
    func_802CD898, func_802CDB18, func_80325340,
    0, 0, 0.0f, 0
}; 

/* .code */
void func_802CD870(Actor *this){
    *(s32 *)this->unkBC = TRUE;
    func_8028F918(2);
}

void func_802CD898(Actor *this){
    marker_despawn(this->marker);
    camera_setType(2);
}

void func_802CD8C0(Actor *this){
    if(!this->volatile_initialized){
        this->volatile_initialized = TRUE;
        this->marker->unk2C_1 = 1;
        this->marker->collidable = FALSE;
        *(s32*)this->unkBC = 0; //TODO Make struct
#if defined(WARP_CAULDRON_MENU) && defined(ADDITIONAL_CHEATS)
        this->state = 0;
#endif
        if(volatileFlag_get(VOLATILE_FLAG_1) || volatileFlag_get(VOLATILE_FLAG_1F_IN_CHARACTER_PARADE)){
            marker_despawn(this->marker);
            return;
        }
/*
 * Adds a check to allow Cauldron Warps to trigger cutscenes. Also checks to make sure if you're not in a Warp Cauldron Cutscene.
 * This is primarily used for the cutscene where you enter FF for the first time.
 * Despawning the object if you enter from the incorrect entrance can prevent the cutscene from playing
 * and the FILEPROG_F4_ENTER_FF_CUTSCENE flag from setting when you reenter FF from the correct entrance.
 * Instead, set the state to 1 if you enter from the incorrect entrance and prevent the cutscene from playing.
 * The state gets reset everytime the map loads, so the cutscene can play properly if you reenter from the correct entrance.
 * 
 * NOTE: This is only possible if you have WARP_CAULDRON_MENU enabled and entered the VOLATILE_FLAG_15_SANDCASTLE_UNLOCK_ALL_CAULDRONS cheat code with ADDITIONAL_CHEATS enabled.
 */
#if defined(WARP_CAULDRON_MENU) && defined(ADDITIONAL_CHEATS)
        if (((this->actorTypeSpecificField != 0x32) && (func_8028E4A4() != this->actorTypeSpecificField) && !volatileFlag_get(VOLATILE_FLAG_1E)) || get_inWarpCauldronCutscene()) {
            this->state = 1;
#else
        if(this->actorTypeSpecificField != 0x32 && func_8028E4A4() != this->actorTypeSpecificField){
            marker_despawn(this->marker);
#endif
            return;
        }
        if(gsworld_get_map() == MAP_26_MMM_NAPPERS_ROOM){
            if(fileProgressFlag_get(FILEPROG_1D_MMM_DINNING_ROOM_CUTSCENE)){
                marker_despawn(this->marker);
                return;
            }
            else{
                func_802CD870(this);
                fileProgressFlag_set(FILEPROG_1D_MMM_DINNING_ROOM_CUTSCENE, TRUE);
            }
        }
        //L802CD9C4
        if(gsworld_get_map() == MAP_8E_GL_FURNACE_FUN){
            if(fileProgressFlag_get(FILEPROG_F4_ENTER_FF_CUTSCENE)){
                marker_despawn(this->marker);
                return;
            }
            else{
                func_802CD870(this);
            }
        }
    }//L802CDA00

#if defined(WARP_CAULDRON_MENU) && defined(ADDITIONAL_CHEATS)
        if (this->state == 1) {
            return;
        }
#endif

    if(func_80343D50(this, func_80343654(this) + 1, 20, 20)){
        func_802CDAC4(this);
        if(1.0 == this->unk48){
            this->marker->unk2C_2 = 0;
            if(*(s32*)this->unkBC)
                func_8028F918(0);
            if(gsworld_get_map() == MAP_8E_GL_FURNACE_FUN){
                mapSpecificFlags_set(4, TRUE);
            }
            else{
                camera_setType(2);
                ncDynamicCamera_setState(0xf);
            }
            marker_despawn(this->marker);
        }
    }
}

void func_802CDAC4(Actor *this){
    f32 sp1C[3];

    camera_setType(1);
    viewport_setPosition_vec3f(this->position);
    sp1C[0] = this->pitch;
    sp1C[1] = this->yaw;
    sp1C[2] = 0.0f;
    viewport_setRotation_vec3f(sp1C);
}

void func_802CDB18(Actor *this){
    func_8028FBD4(0);
    func_802CD8C0(this);
}
