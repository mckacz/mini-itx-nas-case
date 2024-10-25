#include "ui.h"

lv_obj_t *ui_main;
lv_obj_t *ui_container;
lv_obj_t *ui_hex;
lv_obj_t *ui_indicator;
lv_obj_t *ui_spin;
lv_obj_t *ui_spin2;
lv_obj_t *ui_icon;
lv_obj_t *ui_hint;
lv_obj_t *ui_status_container;
lv_obj_t *ui_wifi;
lv_obj_t *ui_time;
lv_obj_t *ui_start_anim;

void hex_animation(lv_obj_t *TargetObject, int delay) {
    auto usr = static_cast<ui_anim_user_data_t*>(lv_mem_alloc(sizeof(ui_anim_user_data_t)));
    usr->target = TargetObject;
    usr->val = -1;

    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_time(&anim, 60000);
    lv_anim_set_user_data(&anim, usr);
    lv_anim_set_values(&anim, 0, 3600);
    lv_anim_set_path_cb(&anim, lv_anim_path_linear);
    lv_anim_set_delay(&anim, delay + 0);
    lv_anim_set_playback_time(&anim, 0);
    lv_anim_set_playback_delay(&anim, 0);
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&anim, 0);
    lv_anim_set_early_apply(&anim, false);

    lv_anim_set_custom_exec_cb(&anim, [](lv_anim_t *a, int32_t v) {
        auto usr = static_cast<ui_anim_user_data_t*>(a->user_data);
        lv_img_set_angle(usr->target, v);
    });

    lv_anim_set_deleted_cb(&anim, [](lv_anim_t *a) {
        lv_mem_free(a->user_data);
        a->user_data = NULL;
    });

    lv_anim_set_get_value_cb(&anim, [](lv_anim_t *a) {
        ui_anim_user_data_t *usr = (ui_anim_user_data_t *) a->user_data;
        return (int32_t) lv_img_get_angle(usr->target);
    });

    lv_anim_start(&anim);
}

void ui_event_start_anim(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_SCREEN_LOAD_START) {
        hex_animation(ui_hex, 0);
    }
}

void ui_init() {
    lv_disp_t *disp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(
        disp,
        lv_palette_main(LV_PALETTE_BLUE),
        lv_palette_main(LV_PALETTE_RED),
        true, LV_FONT_DEFAULT
    );

    lv_disp_set_theme(disp, theme);
    ui_main_screen_init();

    ui_start_anim = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui_start_anim, ui_event_start_anim, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui_start_anim);
    lv_disp_load_scr(ui_main);
}
