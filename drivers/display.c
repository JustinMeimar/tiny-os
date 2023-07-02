#include "display.h"

// Interface Functions
/**
 * Print message at specific coordinate given by (row, col) 
 */
void kprint_at(const char* msg, uint8_t row, uint8_t col)
{
    uint16_t index = get_cursor_index_from_coords(row, col);
    kprint_at_index(msg, index); 
}
/**
 * Print message at cursor position 
 */
void kprint(const char* msg)
{
    uint16_t index = get_cursor_index();
    kprint_at_index(msg, index); 
    set_cursor_index(index + strlen(msg));
}

// Static Functions
/**
 * Core print function for both kprint_at and kprint 
 */
static void kprint_at_index(const char* msg, uint16_t index)
{
    char *video_mem = (char*) VIDEO_MEM;

    uint32_t i = 0; 
    while (msg[i] != '\0') 
    {
        char c = msg[i];
        *(video_mem + (index + i ) * 2) = c;
        *(video_mem + (index + i ) * 2 + 1) = 0x0F;
        i++;
    }
}

/**
 * Write a row from the VGA to another row. Perserve both the character byte and 
 * the styling byte, (unlike kprint which accepts only the character bytes) 
 */
static void write_vga_row(const char* vga_row, uint8_t row)
{
    char *video_mem = ((char *) VIDEO_MEM + (ROW_SIZE * row));
    uint32_t i = 0; 
    while (i < ROW_SIZE)
    {
        video_mem[i] = vga_row[i];
        i++;
    }
}

/**
 * Move every row up one.
 */
void scroll()
{
    char *video_mem = (char *) VIDEO_MEM;
    char row_buf[ROW_SIZE];

    //TODO: Save the first row into a larger buffer for retrieval. 
    uint32_t i = 1;
    while (i < ROW_SIZE)
    {
        char *cur_row = (video_mem + (i * ROW_SIZE));
        memcpy(row_buf, cur_row, ROW_SIZE);
        write_vga_row(row_buf, i-1);
        i++;
    }
    set_cursor_index(get_cursor_index() - MAX_COLS);
    kprint("done scroll");
}

/**
 * Set the cursor index of the VGA display to index;
 */
static void set_cursor_index(uint16_t index)
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
static uint16_t get_cursor_index()
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

static uint16_t get_cursor_index_from_coords(uint8_t row, uint8_t col)
{
    uint16_t index = (uint16_t)(row * MAX_COLS + col);
    return index;
}

static uint8_t get_row_from_cursor_index(uint16_t index)
{
    return (uint8_t)(index / MAX_COLS);
}

static uint8_t get_col_from_cursor_index(uint16_t index)
{
    return (uint8_t)(index % MAX_COLS);
}