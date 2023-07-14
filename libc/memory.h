#ifndef MEMORY_H
#define MEMORY_H
#include "../kernel/types.h"

void *malloc(uint32_t n_bytes);
void memcpy(void *dst, void *src, uint32_t bytes);

#endif