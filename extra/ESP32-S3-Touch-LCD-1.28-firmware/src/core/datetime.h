#pragma once

typedef void (*DateTimeSynchronized)();

void datetime_init();
void datetime_loop();

bool time_synchronized();
struct tm get_time();
time_t get_timestamp();
String format_time(const struct tm &info);
String format_date(const struct tm &info);
void time_onSynchronized(DateTimeSynchronized cb);