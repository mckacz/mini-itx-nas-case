#include <Arduino.h>
#include <WiFi.h>
#include "core/datetime.h"
#include "core/time_utils.h"
#include "core/ota.h"
#include "ui/ui.h"
#include "io/io.h"
#include "lcd/lcd.h"
#include "config.h"
#include "view.h"

bool wifi_state = false;
bool time_sync_state = false;
bool update_status_icons = false;
bool locked = true;
bool updating = false;
bool pulse_set = false;

int power_state = LOW;
bool power_state_changing = false;

uint32_t unlock_start = 0;
uint32_t unlock_hint_start = 0;
uint32_t pressing_start = 0;
uint32_t inactive_start = 0;

int current_view = VIEW_UNDETERMINED;

void view_set_wifi_state(bool state) {
    if (wifi_state != state) {
        wifi_state = state;
        update_status_icons = true;
    }
}

void view_set_time_sync_state(bool state) {
    if (time_sync_state != state) {
        time_sync_state = state;
        update_status_icons = true;
    }
}

int view_detect() {
    if (updating) {
        return VIEW_UPDATING;
    }

    if (power_state == HIGH) {
        return locked ? VIEW_PWR_ON_LOCKED : VIEW_PWR_ON_UNLOCKED;
    }

    return locked ? VIEW_PWR_OFF_LOCKED : VIEW_PWR_OFF_UNLOCKED;
}

void view_go_pwr_off_unlocked() {
    // indicator
    lv_arc_set_value(ui_indicator, 0);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_OFF_INDICATOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_ON_MAIN), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_indicator, LV_OBJ_FLAG_HIDDEN);

    // icon
    lv_img_set_src(ui_icon, &ui_img_switch_png);
    lv_obj_set_style_img_recolor(ui_icon, lv_color_hex(COLOR_OFF_MAIN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_icon, LV_OBJ_FLAG_HIDDEN);

    // hint
    lv_label_set_text(ui_hint, "");
    lv_obj_add_flag(ui_hint, LV_OBJ_FLAG_HIDDEN);
}

void view_go_pwr_off_locked() {
    view_go_pwr_off_unlocked();

    lv_img_set_src(ui_icon, &ui_img_bee_png);
    lv_obj_set_style_opa(ui_icon, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void view_go_pwr_on_unlocked() {
    // indicator
    lv_arc_set_value(ui_indicator, 0);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_ON_INDICATOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_OFF_MAIN), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_indicator, LV_OBJ_FLAG_HIDDEN);

    // icon
    lv_img_set_src(ui_icon, &ui_img_switch_png);
    lv_obj_set_style_img_recolor(ui_icon, lv_color_hex(COLOR_ON_MAIN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_icon, LV_OBJ_FLAG_HIDDEN);

    // hint
    lv_label_set_text(ui_hint, "");
    lv_obj_add_flag(ui_hint, LV_OBJ_FLAG_HIDDEN);
}

void view_go_pwr_on_locked() {
    view_go_pwr_on_unlocked();

    lv_img_set_src(ui_icon, &ui_img_bee_png);
    lv_obj_set_style_opa(ui_icon, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void view_go_updating() {
    // indicator
    lv_arc_set_value(ui_indicator, 0);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_UPDATE_INDICATOR_BG), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_indicator, lv_color_hex(COLOR_UPDATE_INDICATOR), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_indicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_indicator, LV_OBJ_FLAG_HIDDEN);

    // icon
    lv_img_set_src(ui_icon, &ui_img_update_png);
    lv_obj_set_style_img_recolor(ui_icon, lv_color_hex(COLOR_UPDATE_INDICATOR), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_icon, LV_OBJ_FLAG_HIDDEN);

    // hint
    lv_label_set_text(ui_hint, "Updating...");
    lv_obj_clear_flag(ui_hint, LV_OBJ_FLAG_HIDDEN);
}

void view_update_status_icons() {
    if (wifi_state) {
        lv_obj_add_flag(ui_wifi, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_HIDDEN);
    }

    if (time_sync_state) {
        lv_obj_add_flag(ui_time, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(ui_time, LV_OBJ_FLAG_HIDDEN);
    }
}

void view_check() {
    const auto next = view_detect();

    if (next != current_view) {
        switch (next) {
            case VIEW_UPDATING:
                view_go_updating();
                break;

            case VIEW_PWR_ON_LOCKED:
                view_go_pwr_on_locked();
                break;

            case VIEW_PWR_OFF_LOCKED:
                view_go_pwr_off_locked();
                break;

            case VIEW_PWR_ON_UNLOCKED:
                view_go_pwr_on_unlocked();
                break;

            case VIEW_PWR_OFF_UNLOCKED:
            default:
                view_go_pwr_off_unlocked();
                break;
        }

        current_view = next;
    }

    if (current_view == VIEW_UPDATING) {
        lv_obj_clear_flag(ui_container, LV_OBJ_FLAG_HIDDEN);
        lcd_backlight(BL_ACTIVE);

        lv_obj_add_flag(ui_spin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_spin2, LV_OBJ_FLAG_HIDDEN);

        return;
    }

    if (update_status_icons) {
        update_status_icons = false;
        view_update_status_icons();
    }

    if (unlock_hint_start > 0 && elapsed(unlock_hint_start) > UNLOCK_HINT_TIMEOUT) {
        current_view = VIEW_UNDETERMINED;
    }

    if (!locked && elapsed(unlock_start) > LOCK_TIMEOUT) {
        locked = true;
    }

    const auto inactive_time = elapsed(inactive_start);

    if (inactive_time < BL_INACTIVE_TIMEOUT) {
        if (BL_INACTIVE_HIDE_UI) {
            lv_obj_clear_flag(ui_container, LV_OBJ_FLAG_HIDDEN);
        }

        lcd_backlight(BL_ACTIVE);
    } else if (inactive_time > BL_INACTIVE_TIMEOUT && !power_state_changing) {
        if (BL_INACTIVE_HIDE_UI && power_state == LOW) {
            lv_obj_add_flag(ui_container, LV_OBJ_FLAG_HIDDEN);
        }

        lcd_backlight(power_state == HIGH ? BL_INACTIVE_ON : BL_INACTIVE_OFF);
    }

    if (power_state_changing) {
        lv_obj_clear_flag(ui_spin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_spin2, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(ui_spin, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_spin2, LV_OBJ_FLAG_HIDDEN);
    }
}

void view_update_indicator() {
    if (!locked && pressing_start > 0) {
        auto v = static_cast<int16_t>(static_cast<double>(elapsed(pressing_start)) * 100 / PRESS_TIMEOUT);

        if (v > 100) {
            v = 100;
        }

        lv_arc_set_value(ui_indicator, v);

        if (v == 100 && !pulse_set) {
            io_switch();
            pulse_set = true;
        }
    }
}

void click_cb(lv_event_t*) {
    if (locked) {
        lv_img_set_src(ui_icon, &ui_img_lock_png);
        lv_obj_set_style_opa(ui_icon, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(ui_icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_label_set_text(ui_hint, "Swipe to unlock");
        lv_obj_clear_flag(ui_hint, LV_OBJ_FLAG_HIDDEN);

        unlock_hint_start = millis();
    }
}

void pressing_cb(lv_event_t*) {
    inactive_start = millis();

    if (!locked) {
        unlock_hint_start = millis();
    }
}

void pressed_cb(lv_event_t*) {
    if (!locked) {
        pressing_start = millis();
    }
}

void released_cb(lv_event_t*) {
    if (pressing_start > 0) {
        pressing_start = 0;
        lv_arc_set_value(ui_indicator, 0);
        pulse_set = false;
    }
}

void gesture_cb(byte gesture) {
    if (locked && (gesture == GESTURE_SWIPE_RIGHT || gesture == GESTURE_SWIPE_LEFT)) {
        locked = false;
        unlock_start = millis();
    }
}

void view_init() {
    lv_obj_add_event_cb(ui_main, click_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_main, pressing_cb, LV_EVENT_PRESSING, NULL);
    lv_obj_add_event_cb(ui_main, pressed_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(ui_main, released_cb, LV_EVENT_RELEASED, NULL);
    lv_arc_set_rotation(ui_spin2, 90);
    lcd_onGesture(gesture_cb);

    inactive_start = millis();
    lcd_backlight(BL_ACTIVE);
    view_check();

    WiFi.onEvent(
        [](arduino_event_id_t event) {
            view_set_wifi_state(true);
        },
        ARDUINO_EVENT_WIFI_STA_GOT_IP
    );

    WiFi.onEvent(
        [](arduino_event_id_t event) {
            view_set_wifi_state(false);
        },
        ARDUINO_EVENT_WIFI_STA_DISCONNECTED
    );

    time_onSynchronized([] {
        view_set_time_sync_state(true);
    });

    io_onChange([](int current, int desired, bool) {
        power_state = current;
        power_state_changing = current != desired;
        inactive_start = millis();
    });

    ota_onUpdate([](int prc) {
        updating = true;
        view_check();
        lv_arc_set_value(ui_indicator, prc);
        lv_timer_handler();
    });
}

void view_loop() {
    static uint32_t guard50ms;
    static uint32_t guard200ms;

    if (every(50, guard50ms)) {
        view_update_indicator();
    }

    if (every(200, guard200ms)) {
        view_check();
    }
}
