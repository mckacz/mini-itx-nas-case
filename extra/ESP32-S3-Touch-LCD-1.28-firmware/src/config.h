#pragma once

// Wi-Fi credentials
#define WIFI_SSID "my_wifi_name"
#define WIFI_PASS "my_wifi_pass"

// Time after which the module will restart if it could not connect to the Wi-Fi (ms)
#define WIFI_RESTART_AFTER 30000

// Host name for OTA and web server
#define OTA_HOST "button" // should match `upload_port` for `esp32_remote` env in `platformio.ini`
#define OTA_PASS "hax0r"  // should match `auth` in `upload_flags` for `esp32_remote` env in `platformio.ini`

// Time zone
#define TIMEZONE "UTC"
// #define TIMEZONE "CET-1CEST-2,M3.5.0/2,M10.5.0/3" // Poland

// Pin to read power state
#define PWR_GET_PIN 33

// Pin to switch power state
#define PWR_SET_PIN 21

// Time of power switching pulse (ms)
#define PWR_PULSE_TIME 500

// Max. time of power changing (ms)
// Up to this time, switching animation will be displayed when powering off
#define PWR_DESIRED_TIMEOUT 30000

// Unlock hint display time
#define UNLOCK_HINT_TIMEOUT 2000

// Timeout after which the button will be locked automatically
#define LOCK_TIMEOUT 30000

// Required time of pressing to switch the power
#define PRESS_TIMEOUT 1000

// Timeout after which the backlight is switched to inactive state
#define BL_INACTIVE_TIMEOUT 30000

// PWM value of backlight for active state (0-255)
#define BL_ACTIVE 255

// PWM value of backlight for inactive state when powered on (0-255)
#define BL_INACTIVE_ON 192

// PWM value of backlight for inactive state when powered off (0-255)
#define BL_INACTIVE_OFF 0

// Hide UI when inactive and powered off (useful to avoid screen refresh when backlight is set 0)
#define BL_INACTIVE_HIDE_UI 1

// Indicator color when power off
#define COLOR_OFF_INDICATOR 0xAA0000

// Button color when power off
#define COLOR_OFF_MAIN 0xCC0000

// Indicator color when power on
#define COLOR_ON_INDICATOR 0x009900

// Button color when power on
#define COLOR_ON_MAIN 0x00CC00

// Indicator color when updating (OTA)
#define COLOR_UPDATE_INDICATOR 0x0000CC

// Indicator background color when updating (OTA)
#define COLOR_UPDATE_INDICATOR_BG 0x000033
