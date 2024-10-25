#include <vector>
#include <ArduinoOTA.h>
#include <WiFi.h>
#include "config.h"
#include "ota.h"

static std::vector<OTAUpdating> updatingEventCbList;

void ota_init() {
    ArduinoOTA.setHostname(OTA_HOST);
    ArduinoOTA.setPassword(OTA_PASS);
    ArduinoOTA.setMdnsEnabled(true);

    ArduinoOTA.onProgress([](unsigned current, unsigned total) {
        int prc = (current * 100.0) / total;
        static int lastPrc = -1;

        if (lastPrc != prc) {
            lastPrc = prc;

            for (auto &cb: updatingEventCbList) {
                cb(prc);
            }
        }
    });

    WiFi.onEvent(
        [](arduino_event_id_t) {
            ArduinoOTA.begin();
            Serial.println("OTA start");
        },
        ARDUINO_EVENT_WIFI_STA_GOT_IP
    );

    WiFi.onEvent(
        [](arduino_event_id_t) {
            ArduinoOTA.end();
        },
        ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
}

void ota_loop() {
    ArduinoOTA.handle();
}

void ota_onUpdate(OTAUpdating cb) {
    updatingEventCbList.push_back(cb);
}
