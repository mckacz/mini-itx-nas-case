#include <WiFi.h>
#include "config.h"

bool wasConnected = false;

void wifi_init() {
  WiFi.onEvent(
    [](arduino_event_id_t event) {
      Serial.println("Connecting to wi-fi...");
    },
    ARDUINO_EVENT_WIFI_STA_START
  );

  WiFi.onEvent(
    [](arduino_event_id_t event) {
      Serial.printf("Connected to wi-fi\n");
    },
    ARDUINO_EVENT_WIFI_STA_GOT_IP
  );

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
}

void wifi_loop() {
  const bool connected = WiFi.isConnected();

  if (connected && !wasConnected) {
    wasConnected = true;
  }

  if (!wasConnected && !connected && WIFI_RESTART_AFTER < millis()) {
    esp_restart();
  }
}

bool wifi_connected() {
  return WiFi.isConnected();
}
