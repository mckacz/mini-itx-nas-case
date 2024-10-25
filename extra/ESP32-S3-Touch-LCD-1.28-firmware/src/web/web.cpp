#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include "io/io.h"
#include "scheduler/scheduler.h"
#include "web.h"

WebServer server(80);

String getContentType(const String &filename) {
    if (server.hasArg("download")) {
        return "application/octet-stream";
    } else if (filename.endsWith(".htm")) {
        return "text/html";
    } else if (filename.endsWith(".html")) {
        return "text/html";
    } else if (filename.endsWith(".css")) {
        return "text/css";
    } else if (filename.endsWith(".js")) {
        return "application/javascript";
    } else if (filename.endsWith(".png")) {
        return "image/png";
    } else if (filename.endsWith(".gif")) {
        return "image/gif";
    } else if (filename.endsWith(".jpg")) {
        return "image/jpeg";
    } else if (filename.endsWith(".ico")) {
        return "image/x-icon";
    } else if (filename.endsWith(".xml")) {
        return "text/xml";
    } else if (filename.endsWith(".pdf")) {
        return "application/x-pdf";
    } else if (filename.endsWith(".zip")) {
        return "application/x-zip";
    } else if (filename.endsWith(".gz")) {
        return "application/x-gzip";
    }
    return "text/plain";
}

bool fileExists(const String &path){
    bool yes = false;
    File file = SPIFFS.open(path, "r");
    if(!file.isDirectory()){
        yes = true;
    }
    file.close();
    return yes;
}

bool handleFile(String path) {
    if (path.endsWith("/")) {
        path += "index.html";
    }

    const String contentType = getContentType(path);
    const String pathWithGz = path + ".gz";

    if (fileExists(pathWithGz) || fileExists(path)) {
        if (fileExists(pathWithGz)) {
            path += ".gz";
        }

        File file = SPIFFS.open(path, "r");
        server.streamFile(file, contentType);
        file.close();

        return true;
    }

    return false;
}

void handlePowerState() {
    int current = io_read();
    int desired = io_readDesired();

    String output = "{";
    output += "\"state\": " + String(current == HIGH) + ",";
    output += "\"changing\": " + String(current != desired);
    output += "}";

    server.send(200, "text/json", output);
}

void handlePowerSwitch() {
    io_switch();
    server.send(204);
}

void handleScheduleGet() {
    const auto settings = scheduler_get_settings();

    String output = "{";
    output += "\"enabled\": " + String(settings.enabled) + ",";
    output += "\"powerLossOn\": " + String(settings.powerLossOn) + ",";
    output += "\"onTime\": " + String(settings.onTime) + ",";
    output += "\"offTime\": " + String(settings.offTime);
    output += "}";

    server.send(200, "text/json", output);
}

void handleScheduleSet() {
    SchedulerSettings settings;

    settings.enabled = server.pathArg(0) == "1";
    settings.powerLossOn = server.pathArg(1) == "1";
    settings.onTime = server.pathArg(2).toInt();
    settings.offTime = server.pathArg(3).toInt();

    scheduler_set_settings(settings);

    server.send(204, "text/json");
}

void web_init() {
    SPIFFS.begin();

    server.enableCrossOrigin(true);
    server.on("/api/power", HTTP_GET, handlePowerState);
    server.on("/api/power", HTTP_POST, handlePowerSwitch);
    server.on("/api/schedule", HTTP_GET, handleScheduleGet);
    server.on(UriBraces("/api/schedule/{}/{}/{}/{}"), HTTP_POST, handleScheduleSet);

    server.onNotFound([]() {
        if (!handleFile(server.uri())) {
            server.send(404, "text/plain", "FileNotFound");
        }
    });

    WiFi.onEvent(
        [](arduino_event_id_t event) {
            server.begin();
        },
        ARDUINO_EVENT_WIFI_STA_GOT_IP
    );

    WiFi.onEvent(
        [](arduino_event_id_t event) {
            server.close();
        },
        ARDUINO_EVENT_WIFI_STA_DISCONNECTED
    );
}

void web_loop() {
    server.handleClient();
}
