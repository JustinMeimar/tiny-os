#include "display.h"

void kprint_at(const char* msg, uint8_t row, uint8_t col)
{
    uint16_t index = get_cursor_index_from_coords(row, col);
    
}

void kprint(const char* msg)
{
    uint16_t index = get_cursor_index();
    char *video_mem = (char*) VIDEO_MEM;

    uint32_t i = 0; 
    while (msg[i] != '\0') {
        char c = msg[i];
        *(video_mem + (index + i ) * 2) = c;
        *(video_mem + (index + i ) * 2 + 1) = 0x0F;
        i++;
    }
    set_cursor_index(index + i);
    return;
}

/**
 * Set the cursor index of the VGA display to index;
 */
void set_cursor_index(uint16_t index)
{
    /**
    * Set the high byte of the cursor's position. Load register 0x0E into control,
    * then write the high byte to the data port. */
    port_byte_out(VGA_CONTROL_PORT, 0x0E);
    port_byte_out(VGA_DATA_PORT, (uint8_t)((index >> 8) & 0xFF));

    /**
     * Set the low byte of the cursor's position. Load register 0x0F into control,
     * then write the low byte to the data port. */
    port_byte_out(VGA_CONTROL_PORT, 0x0F);
    port_byte_out(VGA_DATA_PORT, (uint8_t)(index & 0xFF));
}

/**
 * 
 * Ask the VGA via port 0x34 for the 
 * High part of the cursor position resides in register 0x0E
 * Low part of the cursor position resides in 0x0F
 */
uint16_t get_cursor_index()
{
    /**
     * Get high byte of the cursor index. Load regsiter 0x0E into control, 
     * then read the high byte, cast into 16-bit from 8-bit and then mask for fun :p */
    port_byte_out(VGA_CONTROL_PORT, 0x0E); //
    uint16_t cursor_high = ((uint16_t) port_byte_in(VGA_DATA_PORT) << 8);

    /**
     * Get the low byte of the cursor index. Load register 0x0F into control, 
     * then read the low byte, cast and mask */
    port_byte_out(VGA_CONTROL_PORT, 0x0F);
    uint16_t cursor_low = ((uint16_t) port_byte_in(VGA_DATA_PORT)) & 0x00FF;
    
    /*
     * Make a logical OR of the high and low to return the cursor index.*/
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