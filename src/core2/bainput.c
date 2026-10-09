#include <ultra64.h>
#include "functions.h"
#include "variables.h"

#include "config.h"

u32 bainput_enableMask;
f32 bainput_diveCooldown;

int bainput_should_beak_barge(void){
    return bakey_pressed(BUTTON_B) && can_beak_barge();
}

int bainput_should_beak_bust(void){
    return bakey_pressed(BUTTON_Z) && can_beak_bust();
}

#ifdef DPAD_FUNCTIONALITY
int bainput_dpad_controls_valid(enum button_e button, bool held) {
    bool active = FALSE;

 #ifdef OPTIONS_MENU
    if (!is_qol_feature_enabled(QOL_ID_DPAD_FUNCTIONALITY))
        return FALSE;
 #endif

    if (held) {
        active = bakey_held(button);
    } else {
        active = bakey_pressed(button);
    }

    return active;
}

int bainput_camera_controls_valid(enum button_e button, bool held, bool dpadButton) {
    bool active = FALSE;

 #ifdef OPTIONS_MENU
    if (!is_qol_feature_enabled(QOL_ID_DPAD_FUNCTIONALITY) && dpadButton)
        return FALSE;
 #endif

    if (held) {
        active = bakey_held(button);
    } else {
        active = bakey_pressed(button);
    }

    return active;
}

enum button_e bainput_change_camera_bindings(enum button_e button) {
 #if defined(OPTIONS_MENU) && defined(CHANGE_CAMERA_BINDINGS)
    if (!is_qol_feature_enabled(QOL_ID_CHANGE_CAMERA_BINDINGS))
        return button;
 #elif !defined(CHANGE_CAMERA_BINDINGS)
        return button;
 #endif

    switch (button) {
        case BUTTON_C_UP:
            return C_CAM_UP;
            break;
        case BUTTON_C_DOWN:
            return C_CAM_DOWN;
            break;
        case BUTTON_C_LEFT:
            return C_CAM_LEFT;
            break;
        case BUTTON_C_RIGHT:
            return C_CAM_RIGHT;
            break;
        case BUTTON_D_UP:
            return DPAD_CAM_UP;
            break;
        case BUTTON_D_DOWN:
            return DPAD_CAM_DOWN;
            break;
        case BUTTON_D_LEFT:
            return DPAD_CAM_LEFT;
            break;
        case BUTTON_D_RIGHT:
            return DPAD_CAM_RIGHT;
            break;
        default:
            return button;
            break;
    }
}

int check_camera_controls(enum button_e original_button, bool held) {
    enum button_e updated_cam_button = bainput_change_camera_bindings(original_button);
    bool dpadButton = FALSE;

    switch (updated_cam_button) {
        case BUTTON_D_UP:
        case BUTTON_D_DOWN:
        case BUTTON_D_LEFT:
        case BUTTON_D_RIGHT:
            dpadButton = TRUE;
            break;
    }

    return bainput_camera_controls_valid(updated_cam_button, held, dpadButton);
}

int check_l_button_camera(enum button_e l_button) {
 #ifdef CHANGE_CAMERA_BINDINGS
    // If the C Up binding is changed, then always have the L button enter first person camera.
    if ((C_CAM_UP == BUTTON_D_UP)
  #ifdef OPTIONS_MENU
        && is_qol_feature_enabled(QOL_ID_CHANGE_CAMERA_BINDINGS)
  #endif
        ) {
        return bainput_camera_controls_valid(l_button, FALSE, FALSE);
    }
 #endif

    return bainput_dpad_controls_valid(l_button, FALSE);
}
#endif

int bainput_should_look_first_person_camera(void){
#ifdef DPAD_FUNCTIONALITY
    return ((check_camera_controls(BUTTON_C_UP, FALSE) || check_l_button_camera(BUTTON_L))
            && can_view_first_person());
#else
    return bakey_pressed(BUTTON_C_UP) && can_view_first_person();
#endif
}

int bainput_should_rotate_camera_left(void){
#ifdef DPAD_FUNCTIONALITY
    return check_camera_controls(BUTTON_C_LEFT, FALSE) && bainput_isEnabled(0);
#else
    return bakey_pressed(BUTTON_C_LEFT) && bainput_isEnabled(0);
#endif
}

int bainput_should_rotate_camera_right(void){
#ifdef DPAD_FUNCTIONALITY
    return check_camera_controls(BUTTON_C_RIGHT, FALSE) && bainput_isEnabled(1);
#else
    return bakey_pressed(BUTTON_C_RIGHT) && bainput_isEnabled(1);
#endif
}

int bainput_should_zoom_out_camera(void){
#ifdef DPAD_FUNCTIONALITY
    return check_camera_controls(BUTTON_C_DOWN, FALSE) && bainput_isEnabled(5);
#else
    return bakey_pressed(BUTTON_C_DOWN) && bainput_isEnabled(5);
#endif
}

#ifdef DPAD_FUNCTIONALITY
int bainput_dpad_should_rotate_camera_left(void) {
    return (check_camera_controls(BUTTON_D_LEFT, TRUE) && bainput_isEnabled(0));
}

int bainput_dpad_should_rotate_camera_right(void) {
    return (check_camera_controls(BUTTON_D_RIGHT, TRUE) && bainput_isEnabled(1));
}

int bainput_dpad_should_zoom_out_camera(void) {
    return (check_camera_controls(BUTTON_D_DOWN, FALSE) && bainput_isEnabled(5));
}

int bainput_dpad_should_zoom_in_camera(void) {
    return (check_camera_controls(BUTTON_D_UP, FALSE) && bainput_isEnabled(2));
}
#endif

int bainput_should_poop_egg(void){
#ifdef DPAD_FUNCTIONALITY
    return ((bakey_pressed(BUTTON_C_DOWN) || bainput_dpad_controls_valid(BUTTON_D_DOWN, FALSE))
            && can_egg());
#else
    return bakey_pressed(BUTTON_C_DOWN) && can_egg();
#endif
}

int bainput_should_shoot_egg(void){
#ifdef DPAD_FUNCTIONALITY
    return ((bakey_pressed(BUTTON_C_UP) || bainput_dpad_controls_valid(BUTTON_D_UP, FALSE))
            && can_egg());
#else
    return bakey_pressed(BUTTON_C_UP) && can_egg();
#endif
}

int bainput_should_feathery_flap(void){
    return bakey_pressed(BUTTON_A) && can_feathery_flap();
}

int bainput_should_flap_flip(void){
    return bakey_pressed(BUTTON_A) && can_flap_flip();
}

int bainput_should_peck(void){
    return bakey_pressed(BUTTON_B) && can_peck();
}

int bainput_should_dive(void){
    return bakey_pressed(BUTTON_B) && (bainput_diveCooldown == 0.0f) && can_dive();
}

int bainput_isEnabled(s32 arg0){
    return bainput_enableMask  & (1 << arg0);
}

int bainput_should_trot(void){
#ifdef DPAD_FUNCTIONALITY
    return ((bakey_pressed(BUTTON_C_LEFT) || bainput_dpad_controls_valid(BUTTON_D_LEFT, FALSE))
            && can_trot());
#else
    return bakey_pressed(BUTTON_C_LEFT) && can_trot();
#endif
}

int bainput_should_wonderwing(void){
#ifdef DPAD_FUNCTIONALITY
    return ((bakey_pressed(BUTTON_C_RIGHT) || bainput_dpad_controls_valid(BUTTON_D_RIGHT, FALSE))
            && can_wonderwing());
#else
    return bakey_pressed(BUTTON_C_RIGHT) && can_wonderwing();
#endif
}

#ifdef TOGGLEABLE_MOVES
int exit_move_check(void) {
    if (getGameMode() == GAME_MODE_3_NORMAL
 #ifdef OPTIONS_MENU
        && is_qol_feature_enabled(QOL_ID_TOGGLEABLE_MOVES)
 #endif
        ) {
        return (bakey_pressed(BUTTON_Z) || bakey_pressed(BUTTON_B));
    // Game modes such as the title screen demos need to use the vanilla controls to not desync.
    } else {
        return bakey_released(BUTTON_Z);
    }
}
#endif

void bainput_reset(void){
    bainput_enableMask = -1;
    bainput_diveCooldown = 0.0f;
}

void bainput_enable(s32 arg0, int arg1){
    if(arg1)
        bainput_enableMask |= (1 <<arg0);
    else
        bainput_enableMask &= ~(1 <<arg0);
}

void bainput_enable2(s32 arg0, s32 arg1, int arg2){
    bainput_enable(arg0, arg2);
    bainput_enable(arg1, arg2);
}

void bainput_setDiveCooldown(int arg0, f32 arg1){
    bainput_diveCooldown = arg1;
}

void bainput_update(void){
    if(bainput_diveCooldown != 0.0f){
       bainput_diveCooldown  = ml_max_f(bainput_diveCooldown - time_getDelta(), 0.0f);
    }
}
