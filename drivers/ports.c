#include "ports.h"

/**  
 * port mapped IO
 * in ~= load 
 * out ~= store
 */

/**
 * move a byte of data from the port into a local variable 
 */
inline uint8_t port_byte_in(uint16_t port)
{
    uint8_t result;
    __asm__ volatile ("in %%dx, %%al" : "=a" (result) : "d" (port));

    return result;
}

/**
 * move a byte of data to the 16-bit port
 */
inline void port_byte_out(uint16_t port, uint8_t data)
{
    __asm__ volatile ("out %%al, %%dx" : : "a" (data), "d" (port));
}