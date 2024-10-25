#include <Arduino.h>
#include <Preferences.h>
#include <ctime>
#include "core/datetime.h"
#include "core/time_utils.h"
#include "io/io.h"
#include "scheduler.h"

Preferences prefs;
SchedulerSettings settings;

time_t next_on_time;
time_t next_off_time;
time_t last_manual_off_time;

auto scheduler_synchronized = false;

time_t get_next_time(int mh, bool last = false) {
    const auto m = mh % 100;
    const auto h = (mh - m) / 100;
    time_t now = time(nullptr);

    tm info;
    localtime_r(&now, &info);

    info.tm_sec = 0;
    info.tm_min = m;
    info.tm_hour = h;

    auto next = mktime(&info);

    if (next <= now && !last) {
        info.tm_mday++;
        next = mktime(&info);
    }

    return next;
}

void update_schedule_times() {
    if (!settings.enabled) {
        return;
    }

    next_on_time = get_next_time(settings.onTime);
    next_off_time = get_next_time(settings.offTime);
}

SchedulerSettings scheduler_get_settings() {
    return settings;
}

void scheduler_set_settings(SchedulerSettings newSettings) {
    settings = newSettings;
    prefs.putBytes("schedule", &settings, sizeof(settings));

    update_schedule_times();
}

void scheduler_init() {
    prefs.begin("schedule");
    prefs.getBytes("schedule", &settings, sizeof(settings));
    prefs.getBytes("manual_off_time", &last_manual_off_time, sizeof(last_manual_off_time));

    time_onSynchronized([] {
        scheduler_synchronized = true;

        if (settings.enabled) {
            update_schedule_times();

            if (settings.powerLossOn && io_read() == LOW) {
                auto now = time(nullptr);
                auto on_time = get_next_time(settings.onTime, true);
                auto off_time = get_next_time(settings.offTime);

                if (now > on_time && now < off_time && last_manual_off_time < on_time) {
                    io_switch(true);
                }
            }
        }
    });

    io_onChange([](int current, int desired, bool schedule) {
        if (current == LOW && desired == LOW && !schedule) {
            last_manual_off_time = time(nullptr);
            prefs.putBytes("manual_off_time", &last_manual_off_time, sizeof(last_manual_off_time));
        }
    });
}

void scheduler_loop() {
    static uint32_t guard = 0;

    if (every(5000, guard)) {
        if (!settings.enabled || !scheduler_synchronized) {
            return;
        }

        auto now = time(nullptr);

        if (now > next_on_time) {
            if (io_read() == LOW) {
                io_switch(true);
            }

            update_schedule_times();
        } else if (now > next_off_time) {
            if (io_read() == HIGH) {
                io_switch(true);
            }

            update_schedule_times();
        }
    }
}
