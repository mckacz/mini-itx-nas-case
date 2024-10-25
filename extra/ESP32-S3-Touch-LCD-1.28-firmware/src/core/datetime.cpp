#include <ctime>
#include <vector>
#include <WiFi.h>
#include "config.h"
#include "datetime.h"

time_t lastTime;
bool synchronized = false;
static std::vector<DateTimeSynchronized> synchronizedEventCbList;

char buffer[50];
tm timeinfo;

bool time_synchronized() {
    if (!synchronized) {
        time_t stamp;
        time(&stamp);

        synchronized = stamp - lastTime > 1000;
    }

    return synchronized;
}

time_t get_timestamp() {
    time_t stamp;
    time(&stamp);

    return stamp;
}

tm get_time() {
    time_t stamp = get_timestamp();

    lastTime = stamp;
    localtime_r(&stamp, &timeinfo);
    strftime(buffer, 50, "%H:%M", &timeinfo);

    return timeinfo;
}

String format_time(const struct tm &info) {
    strftime(buffer, 50, "%H:%M", &info);

    return String(buffer);
}

String format_date(const struct tm &info) {
    strftime(buffer, 50, "%Y-%m-%d", &info);

    return String(buffer);
}

void datetime_init() {
    WiFi.onEvent(
        [](arduino_event_id_t event) {
            configTzTime(TIMEZONE, "pool.ntp.org");
        },
        ARDUINO_EVENT_WIFI_STA_GOT_IP
    );
}

void datetime_loop() {
    if (!synchronized) {
        if (time_synchronized()) {
            const auto tm = get_time();
            Serial.println("Time synchronized: " + format_date(tm) + " " + format_time(tm));

            for (const auto &cb: synchronizedEventCbList) {
                cb();
            }
        } else {
            if (millis() > 2 * WIFI_RESTART_AFTER) {
                esp_restart();
            }
        }
    }
}

void time_onSynchronized(DateTimeSynchronized cb) {
    synchronizedEventCbList.push_back(cb);
}
