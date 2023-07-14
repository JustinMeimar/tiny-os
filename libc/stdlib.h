#ifndef LIBC_H
#define LIBC_H
#include "../kernel/types.h"
#include "../drivers/display.h"

uint32_t strlen(const char *msg);
char *int_to_ascii(uint32_t n, char *buffer);
void reverse(char *bytes);

#endif