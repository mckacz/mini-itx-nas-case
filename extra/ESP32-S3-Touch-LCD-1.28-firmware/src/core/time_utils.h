#pragma once
#include <Arduino.h>

#define delta(x, y) (y > x ? y - x : x - y)
#define elapsed(x) delta(millis(), x)

bool every(uint32_t interval, uint32_t &guard);
