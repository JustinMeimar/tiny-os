#include "display.h"

/**
 * Ask the VGA via port 0x34 for the 
 * High part of the cursor position resides in register 0x0E
 * Low part of the cursor position resides in 0x0F
 */
uint16_t get_cursor_index()
{
    /**
     * Get high byte of the cursor index. Load regsiter 0x0E into control, 
     * then read the high byte, cast into 16-bit from 8-bit and then mask for fun :p
     */
    port_byte_out(VGA_CONTROL_PORT, 0x0E); //
    uint16_t cursor_high = ((uint16_t) port_byte_in(VGA_DATA_PORT) << 8);

    /**
     * Get the low byte of the cursor index. Load register 0x0F into control, 
     * then read the low byte, cast and mask 
     */
    port_byte_out(VGA_CONTROL_PORT, 0x0F);
    uint16_t cursor_low = ((uint16_t) port_byte_in(VGA_DATA_PORT)) & 0x00FF;
    
    /**
     * Make a logical OR of the high and low to return the cursor index.
     */
    return (cursor_high | cursor_low);
}

uint16_t get_cursor_index_from_coords(uint8_t row, uint8_t col)
{
    uint16_t index = (uint16_t)(row * MAX_COLS + col);
    return index;
}

uint8_t get_row_from_cursor_index(uint16_t index)
{
    return (uint8_t)(index / MAX_COLS);
}

uint8_t get_col_from_cursor_index(uint16_t index)
{
    return (uint8_t)(index % MAX_COLS);
}