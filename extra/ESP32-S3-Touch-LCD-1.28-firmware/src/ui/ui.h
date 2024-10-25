// Generated
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

typedef struct ui_anim_user_data_t {
    lv_obj_t * target;
    lv_img_dsc_t ** imgset;
    int32_t imgset_size;
    int32_t val;
} ui_anim_user_data_t;


extern lv_obj_t *ui_main;
extern lv_obj_t *ui_container;
extern lv_obj_t *ui_hex;
extern lv_obj_t *ui_indicator;
extern lv_obj_t *ui_spin;
extern lv_obj_t *ui_spin2;
extern lv_obj_t *ui_icon;
extern lv_obj_t *ui_hint;
extern lv_obj_t *ui_status_container;
extern lv_obj_t *ui_wifi;
extern lv_obj_t *ui_time;


extern lv_obj_t *ui_start_anim;

LV_IMG_DECLARE(ui_img_hex_png);
LV_IMG_DECLARE(ui_img_wifi_png);
LV_IMG_DECLARE(ui_img_time_sync_png);
LV_IMG_DECLARE(ui_img_lock_png);
LV_IMG_DECLARE(ui_img_switch_png);
LV_IMG_DECLARE(ui_img_update_png);

void ui_main_screen_init();
void ui_init();

#ifdef __cplusplus
} /*extern "C"*/
#endif
