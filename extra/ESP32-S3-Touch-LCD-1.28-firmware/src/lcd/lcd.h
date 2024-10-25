#pragma once

#define GESTURE_SWIPE_UP 0x01
#define GESTURE_SWIPE_DOWN 0x02
#define GESTURE_SWIPE_LEFT 0x03
#define GESTURE_SWIPE_RIGHT 0x04
#define GESTURE_SINGLE_CLICK 0x05
#define GESTURE_DOUBLE_CLICK 0x0B
#define GESTURE_LONG_PRESS 0x0C

typedef void (*GestureCb)(byte gesture);

void lcd_init();
void lcd_loop();
void lcd_backlight(uint8_t value);
void lcd_onGesture(GestureCb cb);
