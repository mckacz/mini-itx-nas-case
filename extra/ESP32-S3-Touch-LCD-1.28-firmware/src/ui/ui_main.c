#include "ui.h"

void ui_main_screen_init() {
    ui_main = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_main, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_main, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_main, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_container = lv_obj_create(ui_main);
    lv_obj_remove_style_all(ui_container);
    lv_obj_set_width(ui_container, lv_pct(100));
    lv_obj_set_height(ui_container, lv_pct(100));
    lv_obj_set_align(ui_container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_container, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_container, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_container, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_hex = lv_img_create(ui_container);
    lv_img_set_src(ui_hex, &ui_img_hex_png);
    lv_obj_set_width(ui_hex, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_hex, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_hex, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_hex, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                              LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                              LV_OBJ_FLAG_SCROLL_MOMENTUM |
                              LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_bg_color(ui_hex, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_hex, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_hex, 96, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_indicator = lv_arc_create(ui_container);
    lv_obj_set_width(ui_indicator, lv_pct(100));
    lv_obj_set_height(ui_indicator, lv_pct(100));
    lv_obj_set_align(ui_indicator, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_indicator, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_FLOATING);
    lv_obj_clear_flag(ui_indicator, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_arc_set_value(ui_indicator, 0);
    lv_arc_set_bg_angles(ui_indicator, 0, 360);
    lv_arc_set_rotation(ui_indicator, 90);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(0x660000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(0x00CC00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_indicator, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_opa(ui_indicator, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_spin = lv_spinner_create(ui_container, 5000, 45);
    lv_obj_set_width(ui_spin, lv_pct(100));
    lv_obj_set_height(ui_spin, lv_pct(100));
    lv_obj_set_align(ui_spin, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_spin, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_spin, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(ui_spin, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_spin, 96, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_spin, lv_color_hex(0xFF8D00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_spin, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_spin, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_spin2 = lv_spinner_create(ui_container, 5000, 45);
    lv_obj_set_width(ui_spin2, lv_pct(100));
    lv_obj_set_height(ui_spin2, lv_pct(100));
    lv_obj_set_align(ui_spin2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_spin2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_spin2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(ui_spin2, lv_color_hex(0x4040FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_spin2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_spin2, lv_color_hex(0xFF8D00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_spin2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_rounded(ui_spin2, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_icon = lv_img_create(ui_container);
    lv_img_set_src(ui_icon, &ui_img_lock_png);
    lv_obj_set_width(ui_icon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_icon, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_icon, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_icon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_icon, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_icon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_hint = lv_label_create(ui_container);
    lv_obj_set_width(ui_hint, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_hint, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_hint, 0);
    lv_obj_set_y(ui_hint, 158);
    lv_obj_set_align(ui_hint, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_hint, "Power off");
    lv_obj_add_flag(ui_hint, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_FLOATING);
    lv_obj_set_style_text_color(ui_hint, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_hint, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_hint, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_hint, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_status_container = lv_obj_create(ui_container);
    lv_obj_remove_style_all(ui_status_container);
    lv_obj_set_width(ui_status_container, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_status_container, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_status_container, 0);
    lv_obj_set_y(ui_status_container, 40);
    lv_obj_set_align(ui_status_container, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_status_container, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_status_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_status_container, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_row(ui_status_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_status_container, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_img_create(ui_status_container);
    lv_img_set_src(ui_wifi, &ui_img_wifi_png);
    lv_obj_set_width(ui_wifi, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_wifi, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_wifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_SCROLLABLE);
    lv_img_set_zoom(ui_wifi, 255);
    lv_obj_set_style_img_recolor(ui_wifi, lv_color_hex(0xFF8D00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_time = lv_img_create(ui_status_container);
    lv_img_set_src(ui_time, &ui_img_time_sync_png);
    lv_obj_set_width(ui_time, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_time, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_time, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_time, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_time, LV_OBJ_FLAG_SCROLLABLE);
    lv_img_set_zoom(ui_time, 255);
    lv_obj_set_style_img_recolor(ui_time, lv_color_hex(0xFF8D00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}
