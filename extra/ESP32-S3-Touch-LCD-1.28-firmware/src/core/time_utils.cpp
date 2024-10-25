#include <Arduino.h>
#include "time_utils.h"

bool every(uint32_t interval, uint32_t &guard) {
    bool ret = elapsed(guard) > interval;

    if (ret) {
        guard = millis();
    }

    return ret;
}