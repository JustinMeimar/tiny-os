#ifndef DISPLAY_H
#define DISPLAY_H

#include "ports.h"
#include "../libc/stdlib.h"
#include "../proc/memory.h"
#define MAX_COLS 80
#define MAX_ROWS 25
#define ROW_SIZE (MAX_COLS * 2)
#define VIDEO_MEM 0xb8000

//INTERFACE 
void kprint_at(const char *msg, uint8_t row, uint8_t col);
void kprint(const char *msg);

//HIDDEN
static void kprint_at_index(const char *msg, uint16_t index);
void scroll();

// ESCAPE CHARS
static void handle_escape_char(
    const char c, 
    uint16_t *index, 
    uint32_t *line_count
);

static void set_cursor_index(uint16_t index);
static uint16_t get_cursor_index();
static uint16_t get_cursor_index_from_coords(uint8_t row, uint8_t col);

// convert an index back to column or row
static uint8_t get_row_from_cursor_index(uint16_t index);
static uint8_t get_col_from_cursor_index(uint16_t index);



#endif