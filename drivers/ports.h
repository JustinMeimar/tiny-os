#ifndef PORTS_H
#define PORTS_H
#include "../kernel/types.h"

/**
 * VGA Control port: There are more registers than ports. 
 * Therefore a control port is neccessary to act as a selector for which port
 * to read / write from 
 */
#define VGA_CONTROL_PORT 0x3d4
/**
 * VGA Data port: The port which gets written into (in the case of `in`) 
 * or is read from (int the case of `out`)
 */
#define VGA_DATA_PORT 0x3d5


uint8_t port_byte_in(uint16_t port);

void port_byte_out(uint16_t port, uint8_t data);
#endif