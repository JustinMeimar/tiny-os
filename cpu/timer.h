#ifndef TIMER_H
#define TIMER_H

#include "isr.h"
#include "../libc/stdlib.h"
#include "../kernel/types.h"
#include "../drivers/screen.h"
#include "../libc/stdlib.h"

void init_timer(uint32_t freq);
void sleep(uint32_t n);

#endif
