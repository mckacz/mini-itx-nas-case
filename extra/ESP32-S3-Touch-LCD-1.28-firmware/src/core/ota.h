#pragma once

typedef void (*OTAUpdating)(int);

void ota_init();
void ota_loop();
void ota_onUpdate(OTAUpdating cb);