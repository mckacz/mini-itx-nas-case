#include <vector>
#include "Arduino.h"
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <CST816S.h>
#include "tft_setup.h"
#include "lcd.h"

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[TFT_WIDTH * TFT_HEIGHT / 10];
static std::vector<GestureCb> gestureEventCbList;
uint8_t lcd_bl_value = 255;

TFT_eSPI tft(TFT_WIDTH, TFT_HEIGHT);
CST816S touch(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_IRQ);

void tft_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p) {
    const uint32_t w = (area->x2 - area->x1 + 1);
    const uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *) &color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

void touch_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    const bool touched = touch.available();

    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;

        data->point.x = touch.data.x;
        data->point.y = touch.data.y;

        if (touch.data.gestureID != NONE) {
            for (int i = 0; i < gestureEventCbList.size(); i++) {
                const auto cb = gestureEventCbList[i];
                cb(touch.data.gestureID);
            }
        }
    }
}

void lcd_backlight(uint8_t value) {
    if (value != lcd_bl_value) {
        lcd_bl_value = value;
        analogWrite(TFT_BL, value);
    }
}

void lcd_init() {
    lv_init();

    tft.begin();
    tft.setRotation(0);

    touch.begin();
    touch.enable_auto_standby(10000);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * TFT_HEIGHT / 10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = tft_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touch_read;
    lv_indev_drv_register(&indev_drv);
}

void lcd_loop() {
    lv_timer_handler();
}

void lcd_onGesture(GestureCb cb) {
    gestureEventCbList.push_back(cb);
}
