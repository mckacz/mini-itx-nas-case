#include <Arduino.h>
#include "core/wifi.h"
#include "core/ota.h"
#include "core/datetime.h"
#include "io/io.h"
#include "lcd/lcd.h"
#include "ui/ui.h"
#include "view/view.h"
#include "scheduler/scheduler.h"
#include "web/web.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Starting...");
    delay(1000);

    lcd_init();
    ui_init();
    view_init();
    io_init();
    ota_init();
    datetime_init();
    wifi_init();
    web_init();
    scheduler_init();
}

void loop() {
    wifi_loop();
    ota_loop();
    view_loop();
    lcd_loop();
    datetime_loop();
    io_loop();
    web_loop();
    scheduler_loop();
    delay(1);
}
