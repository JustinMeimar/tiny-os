#ifndef TIMER_H
#define TIMER_H

#include "../libc/stdlib.h"
#include "../kernel/types.h"

void init_timer(uint32_t freq);
void sleep(uint32_t n);

#endif
