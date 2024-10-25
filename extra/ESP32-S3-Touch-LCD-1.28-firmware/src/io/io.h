#pragma once

typedef void (*PwrChange)(int current, int desired, bool schedule);

void io_init();
void io_loop();
void io_switch();
void io_switch(bool schedule);
int io_read();
int io_readDesired();
void io_onChange(PwrChange cb);