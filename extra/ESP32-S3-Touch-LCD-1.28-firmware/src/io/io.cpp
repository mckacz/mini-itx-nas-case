#include <vector>
#include <Arduino.h>
#include "core/time_utils.h"
#include "config.h"
#include "io.h"

int ioPwrState = 0;
int ioPwrDesiredState = 0;
uint32_t ioPwrDesiredChangeTime = 0;
static std::vector<PwrChange> changeEventCbList;

void io_triggerChange(bool schedule = false) {
    for (auto cb: changeEventCbList) {
        cb(ioPwrState, ioPwrDesiredState, schedule);
    }
}

void io_init() {
    pinMode(PWR_GET_PIN, INPUT_PULLDOWN);
    pinMode(PWR_SET_PIN, OUTPUT);
    digitalWrite(PWR_SET_PIN, LOW);

    ioPwrState = digitalRead(PWR_GET_PIN);
    ioPwrDesiredState = ioPwrState;

    io_triggerChange();
}

void io_loop() {
    static uint32_t guard = 0;

    if (every(500, guard)) {
        auto state = digitalRead(PWR_GET_PIN);

        if (state != ioPwrState) {
            ioPwrState = state;
            ioPwrDesiredState = state;
            io_triggerChange();
        } else if (state != ioPwrDesiredState && elapsed(ioPwrDesiredChangeTime) > PWR_DESIRED_TIMEOUT) {
            ioPwrDesiredState = state;
            io_triggerChange();
        }
    }
}

void io_switch() {
    io_switch(false);
}

void io_switch(bool schedule) {
    ioPwrDesiredState = ioPwrState == HIGH ? LOW : HIGH;
    ioPwrDesiredChangeTime = millis();
    io_triggerChange(schedule);

    digitalWrite(PWR_SET_PIN, HIGH);
    delay(PWR_PULSE_TIME);
    digitalWrite(PWR_SET_PIN, LOW);
}

int io_read() {
    return ioPwrState;
}

int io_readDesired() {
    return ioPwrDesiredState;
}

void io_onChange(PwrChange cb) {
    changeEventCbList.push_back(cb);
}
