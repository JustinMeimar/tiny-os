#ifndef LIBC_H
#define LIBC_H
#include "../kernel/types.h"
#include "../drivers/display.h"

void memcpy(void *dst, void *src, uint32_t bytes);
uint32_t strlen(const char *msg);
char *int_to_ascii(uint32_t n, char *buffer);

// test
void test_stdlib();
static uint8_t test_strlen();
static uint8_t test_memcpy();

#endif