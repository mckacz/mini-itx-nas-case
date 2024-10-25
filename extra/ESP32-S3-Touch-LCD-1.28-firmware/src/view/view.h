#pragma once

#define VIEW_UNDETERMINED         0
#define VIEW_PWR_OFF_LOCKED       1
#define VIEW_PWR_ON_LOCKED        2
#define VIEW_PWR_OFF_UNLOCKED     3
#define VIEW_PWR_ON_UNLOCKED      4
#define VIEW_UPDATING             5

void view_init();
void view_loop();