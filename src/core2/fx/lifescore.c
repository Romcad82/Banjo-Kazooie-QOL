#include <ultra64.h>
#include "core1/core1.h"
#include "functions.h"
#include "variables.h"



extern f32 func_802FB0E4(struct8s*);

/* .code */
#ifdef BUG_FIXES
enum asset_e D_8036A260[] = {0x7E0, 0x7E1, 0x7E2, 0x7E3, 0x7E4, 0x7E4}; // Additional element needed since the calculation to get sprite assets was changed and an extra index could be accessed.
#else
enum asset_e D_8036A260[] = {0x7E0, 0x7E1, 0x7E2, 0x7E3, 0x7E4};
#endif
Gfx D_8036A278[] =
{
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsSPSetGeometryMode(G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};


/* .bss */
void *D_80381EB0[2];
f32 D_80381EB8;
f32 D_80381EBC;
s32 D_80381EC0;
s32 D_80381EC4;
char code_78E50_ItemValueString[8];
struct7s D_80381ED0;

/* .code */
s32 func_802FFDE0(s32 arg0){
    return D_8036A260[arg0/4];
}

s32 func_802FFE04(void){
    s32 v1;
    v1 = MIN(5 , itemPrint_getValue(ITEM_14_HEALTH));
    return (5 - v1)*4;
}

struct7s *fxlifescore_new(s32 item_id){
    s32 i;

    D_80381EB8 = 1.0f;
    D_80381EBC = (f32)func_802FFE04();
    D_80381EC0 = func_802FFDE0((s32)D_80381EBC);
    D_80381EC4 = 0;
    for(i = 0; i < 2; i++){
        D_80381EB0[i] = NULL;
    }
    return &D_80381ED0;
}

void fxlifescore_free(s32 item_id, struct8s *arg1){
    s32 i;
    for(i = 0; i < 2; i++){
        if(D_80381EB0[i] != NULL){
           assetCache_free(D_80381EB0[i]);
           D_80381EB0[i] = NULL;
        }
    };
}

void fxlifescore_draw(enum item_e item_id, struct8s *arg1, Gfx **gfx, Mtx **mtx, Vtx **vtx) {
    s32 sp10C;
    Vtx *sp108;
    s32 sp104;
    s32 var_v0;
    s32 var_v1;
    s32 var_s5;
    s32 var_s4;
    s32 spF0;
    s32 spEC;
    s32 spE8;
    s32 spE4;
    s32 spE0;
    s32 spDC;
#ifdef BUG_FIXES
    f32 animFrame = D_80381EBC;
#endif

    sp10C = -1;
    sp108 = *vtx;
    code_78E50_ItemValueString[0] = '\0';
    strIToA(code_78E50_ItemValueString, MIN(9, itemPrint_getValue(item_id)));
    print_bold_spaced(0x4E, (s32) (func_802FB0E4(arg1) + -16.0f + 4.0f), (char *) &code_78E50_ItemValueString);
    if(1); //fake
    if (D_80381EB0[D_80381EC4] != NULL) {
        gSPDisplayList((*gfx)++, D_8036A278);
        viewport_setRenderViewportAndOrthoMatrix(gfx, mtx);
        if(gfx);
        gDPPipeSync((*gfx)++);
        gDPSetCombineLERP((*gfx)++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor((*gfx)++, 0, 0, 0x00, 0x00, 0x00, 0xFF);
        do{  
/*
 * Fixes an issue where reloading from a death would show the wrong health sprite for the first frame of animation.
 * It was particularly noticable since the animation doesn't start until a second after the hud appears.
 */
#ifdef BUG_FIXES
            /* 
             * When "D_80381EBC" is 20, it shows the sad BK sprite. But when it lowers to 19, it would then abruptly switch to the dead BK sprite.
             * Now, when "D_80381EBC" is 20, just cap the animation frame to 19.
             */
            if (D_80381EBC == 20) {
                animFrame -= 1;
            }
            func_80348044(gfx, D_80381EB0[D_80381EC4], (s32) animFrame % 4, 0, 0, 0, 0, 2, 2, &spF0, &spEC, &spE8, &spE4, &spE0, &spDC, &sp10C);
#else
            func_80348044(gfx, D_80381EB0[D_80381EC4], (s32) D_80381EBC % 4, 0, 0, 0, 0, 2, 2, &spF0, &spEC, &spE8, &spE4, &spE0, &spDC, &sp10C);
#endif
            
            if (((*vtx - sp108) & 0xF) == 0) {
                gSPVertex((*gfx)++, *vtx, MIN(0x10, (1 + sp10C) << 2), 0);
                sp104 = 0;
            } else {
                sp104 = sp104 + 4;
            }

            var_s5 = (40.0f - ((f32) gFramebufferWidth / 2)) + spE0;
            var_s4 = (((((f32) gFramebufferHeight / 2) - func_802FB0E4(arg1)) - -16.0f) - spDC);
            for(var_v1 = 0; var_v1 < 2; var_v1++){
                for(var_v0 = 0; var_v0 < 2; var_v0++){
                        (*vtx)->v.ob[0] = (s16) (s32) (((((f32) spF0 * D_80381EB8 * (f32) var_v0) - (((f32) spE8 * D_80381EB8) / 2)) + var_s5) * 4.0f);
                        (*vtx)->v.ob[1] = (s16) (s32) ((((((f32) spE4 * D_80381EB8) / 2) - ((f32) spEC * D_80381EB8 * var_v1)) + var_s4) * 4.0f);
                        (*vtx)->v.ob[2] = -0x14;
                        (*vtx)->v.tc[0] = ((spF0 - 1) * var_v0) << 6;
                        (*vtx)->v.tc[1] = ((spEC - 1) * var_v1) << 6;
                        (*vtx)++;
                }
            }
            gSP1Quadrangle((*gfx)++, sp104, sp104 + 1, sp104 + 3, sp104 + 2, 0);
        }while(sp10C != 0);
        gDPPipeSync((*gfx)++);
        gDPSetTextureLUT((*gfx)++, G_TT_NONE);
        gDPPipelineMode((*gfx)++, G_PM_NPRIMITIVE);
        viewport_setRenderViewportAndPerspectiveMatrix(gfx, mtx);
    }
}

void fxlifescore_update(enum item_e item_id, struct8s *arg1) {
    s32 var_v0;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    sp20 = (s32) ((f32) func_802FFE04() - D_80381EBC);
    switch (func_802FB0D4(arg1)) {
        case 1:
            if (D_80381EB0[D_80381EC4] == NULL) {
// The "D_80381EBC" variable is a multiple of 4, but was incorrectly divided by 5. This gave the wrong index and loaded an incorrect health sprite when you went into a new area.
#ifdef BUG_FIXES
                D_80381EB0[D_80381EC4] = assetcache_get(D_8036A260[(s32) D_80381EBC / 4]);
#else
                D_80381EB0[D_80381EC4] = assetcache_get(D_8036A260[(s32) D_80381EBC / 5]);
#endif
            }
            break;

        case 0:
            fxlifescore_free(item_id, arg1);
            break;

        case 2:
            if (sp20 != 0) {
                var_v0 = (sp20 >= 0) ? sp20 : -sp20;
                D_80381EBC = D_80381EBC + (0.5 * (sp20 / var_v0));
            }
            sp18 = func_802FFDE0((s32)D_80381EBC);
            if (sp18 != D_80381EC0) {
                D_80381EC4 = NOT(D_80381EC4);
                if (D_80381EB0[D_80381EC4] != 0) {
                    assetCache_free(D_80381EB0[D_80381EC4]);
                }
                D_80381EB0[D_80381EC4] = assetcache_get(sp18);
                D_80381EC0 = sp18;
            }
            break;
    }
}
