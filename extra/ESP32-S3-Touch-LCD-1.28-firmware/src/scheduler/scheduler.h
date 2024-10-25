#pragma once

struct SchedulerSettings {
    bool enabled;
    bool powerLossOn;
    int onTime;
    int offTime;
};

void scheduler_init();
void scheduler_loop();

SchedulerSettings scheduler_get_settings();
void scheduler_set_settings(SchedulerSettings settings);