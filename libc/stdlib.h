#ifndef LIBC_H
#define LIBC_H
#include "../kernel/types.h"
#include "../drivers/display.h"

/**
 * Scuffed memcpy implementation :~| 
 */
void memcpy(void *dst, void *src, uint32_t bytes);
uint32_t strlen(const char *msg);
#endif


// test
static uint8_t test_strlen();
static uint8_t test_memcpy();
void test_stdlib();